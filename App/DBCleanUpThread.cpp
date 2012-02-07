//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "DBCleanUpThread.h"
#include "DBSubSystem.h"
#include "DBTokens.h"
#include "CertificateMaster.h"
#include "SecServTokenId.h"
#include "SSQuickMail.h"
#include "SSConfigPerformance.h"

#ifdef _DEBUG
extern bool g_bTraceUnlock;
#endif

//--------------------------------------------------------------------------------
CDBCleanUpThread::CDBCleanUpThread(CDBSubSystem* pParent)
		: CTypedThreadObject<CSecuritySystem, CDBSubSystem>(pParent)
	{
	}

//--------------------------------------------------------------------------------
bool CDBCleanUpThread::Init()
	{
	SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
	return true;
	}

// keep the certificate and token lists clean
//--------------------------------------------------------------------------------
bool CDBCleanUpThread::MainLoop()
	{
	return DoCleanUp();
	}

//--------------------------------------------------------------------------------
bool CDBCleanUpThread::DoCleanUp()
	{
	CWriteLock lock(GetSubSystem()->GetCertMasters(), false);
	if(! lock.Lock(10000))
		return true;

	CCertificateMaster* pCurCert = (CCertificateMaster*) GetSubSystem()->GetCertMasters()->GetNextAndReQueue();
	if(pCurCert == NULL)
		return true;

	// allow an extra 10 seconds
	LONGLONG nElapsed = ((CTime::GetCurrentTime() - pCurCert->GetLastRefresh()).GetTotalSeconds()) - 10;

	// check to see if the certificate has not been refreshed in the alloted time
	if((nElapsed > pCurCert->GetSecondsToLive()) || pCurCert->GetSecondsToLive() == 0)
		{
		GetSystem()->GetIOSubSystem()->FormatOutput(IOMASK_1, "removing certificate %ld", pCurCert->GetId());

		GetSubSystem()->GetCertMasters()->Remove(pCurCert);

		POSITION pos = pCurCert->GetTokenMap()->GetStartPosition();

		// are there any tokens associated with this cert?
		while(pos != NULL)
			{
			CDBTokenInfo* pTokInfo;
			ULONG nId;
			pCurCert->GetTokenInfoMap()->GetNextAssoc(pos, nId, pTokInfo);
			if(pTokInfo == NULL)
				continue;
			CWriteLock lock(pTokInfo->m_pCertificates, false);
			if(lock.Lock(30000))
				{
				// remove the certificate from the token info
				// the certificate may have had several allocations on this token
				// so retain the count
				int nCount = pTokInfo->m_pCertificates->Remove(pCurCert);

				if(::InterlockedExchangeAdd((long*) &pTokInfo->m_nInUse, -nCount) < 0)
					::InterlockedExchange((long*) &pTokInfo->m_nInUse, 0);
				}
			}

		// the cert is no longer valid
		delete pCurCert;
		}

	return true;
	}

//--------------------------------------------------------------------------------
void CDBCleanUpThread::OnMessage(UINT nMsg, WPARAM, LPARAM)
	{
	if(nMsg == CDBSubSystem::MsgCleanUp)
		DoCleanUp();
	}

//--------------------------------------------------------------------------------
DWORD CDBCleanUpThread::GetThreadLoopSleepInterval() const
	{
	CSSConfigPerformance config;
	if(config.m_nDBCleanupInterval < 20)
		return 20;
	if(config.m_nDBCleanupInterval > 360000)
		return 360000;
	return config.m_nDBCleanupInterval;
	}
