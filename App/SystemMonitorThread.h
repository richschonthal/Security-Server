//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#ifndef _SYSTEMMONITORTHREAD_H_
#define _SYSTEMMONITORTHREAD_H_

//--------------------------------------------------------------------------------
#include <LockedSocket.h>
#include <ThreadObject.h>

//--------------------------------------------------------------------------------
class CMonitorSubSystem;
class CSecuritySystem;

//--------------------------------------------------------------------------------
class CSystemMonitorThread : public CTypedThreadObject<CSecuritySystem, CMonitorSubSystem>
	{
	private:
		CLockedSocket* m_pSocket;

	public:
		CSystemMonitorThread(CMonitorSubSystem*);
		~CSystemMonitorThread();

		virtual bool Init();
		virtual bool MainLoop();
	};

#endif //_SYSTEMMONITORTHREAD_H_
