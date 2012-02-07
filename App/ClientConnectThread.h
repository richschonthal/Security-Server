//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#if !defined(AFX_CLIENTCONNECTTHREAD_H__0BCE52F3_D26F_11D3_AF12_005004A1C5F3__INCLUDED_)
#define AFX_CLIENTCONNECTTHREAD_H__0BCE52F3_D26F_11D3_AF12_005004A1C5F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------------------------------------------------------
#include <ThreadObject.h>

//--------------------------------------------------------------------------------
class CSecuritySystem;
class CClientSubSystem;
class CSmallSocket;

//--------------------------------------------------------------------------------
class CClientConnectThread : public CTypedThreadObject<CSecuritySystem, CClientSubSystem>
	{
	private:
		CSmallSocket* m_pSocket;

	public:
		CClientConnectThread(CClientSubSystem*);
		virtual ~CClientConnectThread();

	// override functions
	public:
		virtual bool MainLoop();

		virtual bool Init();
		virtual void Exit(bool);

	public:
		virtual DWORD GetThreadLoopSleepInterval() const;
	};

#endif // !defined(AFX_CLIENTCONNECTTHREAD_H__0BCE52F3_D26F_11D3_AF12_005004A1C5F3__INCLUDED_)
