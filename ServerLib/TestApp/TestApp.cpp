// TestApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestApp.h"
#include "TestAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAppApp

BEGIN_MESSAGE_MAP(CTestAppApp, CWinApp)
	//{{AFX_MSG_MAP(CTestAppApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAppApp construction

CTestAppApp::CTestAppApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestAppApp object

CTestAppApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestAppApp initialization

#include <ChangeNotificationSubSystem.h>
#include <ChangeNotificationObj.h>

class CTestThread : public CThreadObject
	{
	public:
		CTestThread();

		virtual void OnMessage(UINT, WPARAM, LPARAM);
	};

CTestThread::CTestThread()
: CThreadObject(NULL)
	{
	}

void CTestThread::OnMessage(UINT nMsg, WPARAM pParam, LPARAM)
	{
	if(nMsg == CChangeNotificationSubSystem::MsgChangeNotify)
		{
		CFileChangeNotificationObj* pObj = (CFileChangeNotificationObj*) pParam;
//		TRACE("CHANGE: %s ", pObj->GetActionName());
		if(pObj->m_nAction == FILE_ACTION_RENAMED_NEW_NAME)
			TRACE("%s to %s\n", pObj->m_pOldFilename, pObj->m_pFilename);
		else
			TRACE("%s\n", pObj->m_pFilename);
		delete pObj;
		}
	}

BOOL CTestAppApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CTestThread* pThread = new CTestThread;
	pThread->StartThread();

	CSystem system;
	CChangeNotificationSubSystem sub(&system);
	system.SetState(STATE_RUN);
	sub.AddWatch("c:\\temp", pThread, CChangeNotificationSubSystem::MsgChangeNotify, true);

	CTestAppDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	system.SetState(STATE_EXIT);
	system.WaitForStateSync();

//	delete pThread;
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
