//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#if !defined(AFX_SSIOTHREAD_H__C10D0D11_CF6E_11D3_AF12_005004A1C5F3__INCLUDED_)
#define AFX_SSIOTHREAD_H__C10D0D11_CF6E_11D3_AF12_005004A1C5F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------------------------------------------------------
#include <ThreadObject.h>

//--------------------------------------------------------------------------------
class CSecuritySystem;
class CSSIOSubSystem;

//--------------------------------------------------------------------------------
class CSSIOThread : public CTypedThreadObject<CSecuritySystem, CSSIOSubSystem>
	{
	public:
		CSSIOThread(CSSIOSubSystem*);
		virtual ~CSSIOThread();

		virtual void OnMessage(UINT, WPARAM, LPARAM);
		void Output(LPCTSTR);

		virtual bool Init();
		virtual void Exit(bool);
	};

#endif // !defined(AFX_SSIOTHREAD_H__C10D0D11_CF6E_11D3_AF12_005004A1C5F3__INCLUDED_)
