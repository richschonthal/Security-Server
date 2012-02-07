//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "CertificateMaster.h"

#include "DBTokens.h"

#include <ReadLock.h>
#include <WriteLock.h>
#include <AllocString.h>

//--------------------------------------------------------------------------------
CCertificateMaster::CCertificateMaster()
		: m_pIP(NULL)
		, m_pTokenInfoMap(new CDBTokenInfoMap)
		, m_ctLastRefresh(0)
	{

	}

//--------------------------------------------------------------------------------
CCertificateMaster::~CCertificateMaster()
	{
	delete m_pTokenInfoMap;
	delete[] m_pIP;
	}

//--------------------------------------------------------------------------------
LPCTSTR CCertificateMaster::GetIP() const
	{
	return m_pIP;
	}

//--------------------------------------------------------------------------------
void CCertificateMaster::SetIP(LPCTSTR pIP)
	{
	CWriteLock lock(this, false);
	if(! lock.Lock(30000))
		return;

	delete[] m_pIP;
	m_pIP = NULL;
	AllocString(m_pIP, pIP);
	}

//--------------------------------------------------------------------------------
CTime CCertificateMaster::GetLastRefresh()
	{
	return m_ctLastRefresh;
	}

//--------------------------------------------------------------------------------
void CCertificateMaster::SetLastRefresh(CTime ctTime)
	{
	::InterlockedExchange(reinterpret_cast<long*>(&m_ctLastRefresh), ctTime.GetTime());
#pragma message("Rich says: this is old, pre-64-bit-world code!")
	}

//--------------------------------------------------------------------------------
CDBTokenInfoMap* CCertificateMaster::GetTokenInfoMap()
	{
	return m_pTokenInfoMap;
	}
