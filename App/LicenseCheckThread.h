//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#ifndef _LICENSECHECKTHREAD_H_
#define _LICENSECHECKTHREAD_H_

//--------------------------------------------------------------------------------
#include <ThreadObject.h>

//--------------------------------------------------------------------------------
class CSecuritySystem;

//--------------------------------------------------------------------------------
class CLicenseCheckThread : public CTypedThreadObject<CSecuritySystem, CSecuritySystem>
	{
	private:
		bool m_bRunOk;
		bool m_bFirstRun;
		CTime m_ctLastCheckLicFile;

	public:
		CLicenseCheckThread(CSecuritySystem*);

	private:
		virtual bool Init();
		virtual bool MainLoop();
		virtual DWORD GetThreadLoopSleepInterval() const;
		void DoChecking();
	};

#endif // _LICENSECHECKTHREAD_H_
