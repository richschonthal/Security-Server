//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#ifndef _SSSUBSYSTEM_H_
#define _SSSUBSYSTEM_H_

//--------------------------------------------------------------------------------
#include "SecuritySystem.h"

class CSSIOSubSystem;
class CDBSubSystem;
class CClientSubSystem;
class CSecuritySystem;

//--------------------------------------------------------------------------------
template<class BASECLASS>
class CSSSubSystem : public BASECLASS
	{
	private:
		CSSIOSubSystem* m_pIO;
		CDBSubSystem* m_pDB;
		CClientSubSystem* m_pClient;

	public:
		CSSSubSystem(CSecuritySystem* pSystem)
				: BASECLASS(pSystem), m_pIO(NULL) , m_pDB(NULL) , m_pClient(NULL) {}

	};

/*
//--------------------------------------------------------------------------------
class CSSLBSubSystem : public CLoadBalancedSubSystem
	{
	private:
		CSSIOSubSystem* m_pIO;
		CDBSubSystem* m_pDB;
		CClientSubSystem* m_pClient;

	public:
		CSSLBSubSystem(CSecuritySystem*);

		CSSIOSubSystem* GetIO();
		CDBSubSystem* GetDB();
		CClientSubSystem* GetClientSubSystem();
	};
*/

#endif // _SSSubSystem_H_
