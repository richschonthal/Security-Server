//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "SecurityServerService.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//--------------------------------------------------------------------------------
static LPCTSTR g_pName = "Security Server";

//--------------------------------------------------------------------------------
CSecurityServerService::CSecurityServerService()
		: CNTService(::AfxGetApp())
	{
	}

//--------------------------------------------------------------------------------
CSecurityServerService::~CSecurityServerService()
	{
	}

//--------------------------------------------------------------------------------
LPCTSTR CSecurityServerService::GetServiceName()
	{
	return g_pName;
	}

//--------------------------------------------------------------------------------
LPCTSTR CSecurityServerService::GetDisplayName()
	{
	return g_pName;
	}

//--------------------------------------------------------------------------------
DWORD CSecurityServerService::GetStopPendingTime()
	{
	return 15000;
	}
