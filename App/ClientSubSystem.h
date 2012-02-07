//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#if !defined(AFX_CLIENTSUBSYSTEM_H__3FFF6999_C933_11D3_AF10_005004A1C5F3__INCLUDED_)
#define AFX_CLIENTSUBSYSTEM_H__3FFF6999_C933_11D3_AF10_005004A1C5F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------------------------------------------------------
#include <SubSystem.h>

//--------------------------------------------------------------------------------
class CSecuritySystem;
class CSSConfigClientHandler;
class CClientConnectThread;
class CMagicNumber;

//--------------------------------------------------------------------------------
class CClientSubSystem : public CTypedThreadPoolSubSystem<CSecuritySystem>
	{
	public:
		DECLARE_DYNAMIC(CClientSubSystem);

	protected:
		CSSConfigClientHandler* m_pConfig;
		CClientConnectThread* m_pConnectionThread;

	public:
		enum
			{
			MSG_NEWCONNECTION = WM_USER
			};

	public:
		CClientSubSystem(CSecuritySystem*);
		virtual ~CClientSubSystem();

		CMagicNumber* GetMagNumGen() const;
	};

#endif // !defined(AFX_CLIENTSUBSYSTEM_H__3FFF6999_C933_11D3_AF10_005004A1C5F3__INCLUDED_)
