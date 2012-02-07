//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#ifndef _BACKUPTHREAD_CPP_
#define _BACKUPTHREAD_CPP_

//--------------------------------------------------------------------------------
#include "SSConfigBackup.h"

class CBackupServerConnection;
class CSecuritySystem;
class CSmallSocket;

//--------------------------------------------------------------------------------
class CBackupThread : public CTypedThreadObject<CSecuritySystem, CSecuritySystem>
	{
	private:
		CTime m_ctStarted;

	public:
		CBackupThread(CSecuritySystem*);
		virtual ~CBackupThread();

	private:
		virtual bool MainLoop();
		virtual bool Init();

		virtual DWORD GetThreadLoopSleepInterval() const;

		bool ConnectToMainServer();
	};

#endif // _BACKUPTHREAD_CPP_
