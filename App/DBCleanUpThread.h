//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#ifndef _DBCLEANUPTHREAD_H_
#define _DBCLEANUPTHREAD_H_

//--------------------------------------------------------------------------------
#include <ThreadObject.h>

class CDBSubSystem;
class CSecuritySystem;

//--------------------------------------------------------------------------------
class CDBCleanUpThread : public CTypedThreadObject<CSecuritySystem, CDBSubSystem>
	{
	public:
		CDBCleanUpThread(CDBSubSystem*);

		virtual DWORD GetThreadLoopSleepInterval() const;

		virtual bool MainLoop();
		virtual void OnMessage(UINT, WPARAM, LPARAM);

		virtual bool Init();

		bool DoCleanUp();
	};

#endif // _DBCLEANUPTHREAD_H_
