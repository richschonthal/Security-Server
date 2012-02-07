//--------------------------------------------------------------------------------
//
// Copyright (c) 1999 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
#if !defined(AFX_SUBSYSTEM_H__9F10BA2A_835B_11D3_B0D3_00A0CC271D0D__INCLUDED_)
#define AFX_SUBSYSTEM_H__9F10BA2A_835B_11D3_B0D3_00A0CC271D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------------------------------------------------------
#include "SystemControlObject.h"
#include <StdobjQueue.h>

//--------------------------------------------------------------------------------
class CSystem;
class CThreadObject;

//--------------------------------------------------------------------------------
class CSubSystem : public CSystemControlObject
	{
	protected:
		DECLARE_DYNAMIC(CSubSystem)
		friend class CThreadObject;

	protected:
		CEvent m_event;

	public:
		CSubSystem(CSystem*);
		virtual ~CSubSystem();

		// returns a ptr to the system this sub system is a part of
		CSystem* GetSystem();

		// called by CSystem
		virtual bool Init();
	};

//--------------------------------------------------------------------------------
class CThreadPoolSubSystem : public CSubSystem
	{
	DECLARE_DYNAMIC(CThreadPoolSubSystem)

	friend class CThreadObject;

	protected:
		CQueue<CThreadObject*, CThreadObject*> m_threads;
		LONG m_nBusyThreadCount;
		DWORD m_nProcessorCount;

	public:

		CThreadPoolSubSystem(CSystem*);
		virtual ~CThreadPoolSubSystem();

		// posts a message to all threads
		virtual bool PostMessage(UINT, WPARAM = 0, LPARAM = 0);

		// posts a message to the next thread in the pool
		virtual bool PostNextThreadMessage(UINT, WPARAM = 0, LPARAM = 0);

		// adds a thread to the thread pool
		// if count == -1, one thread is added for each processor in the system
		virtual bool AddThread(CRuntimeClass*, int nCount = -1);

		virtual void AddThread(CThreadObject*);

		LONG GetBusyThreadCount();

		bool WaitForAllToExit(DWORD = INFINITE);

		virtual CThreadObject* CreateThread(CRuntimeClass* = NULL);

	protected:
		void IncBusyThreadCount();
		void DecBusyThreadCount();
	};

//--------------------------------------------------------------------------------
template<class T_SYSTEM>
class CTypedSubSystem : public CSubSystem
	{
	private:
		T_SYSTEM* m_pSystem;

	public:
		CTypedSubSystem(T_SYSTEM* = NULL);
		virtual ~CTypedSubSystem();

		T_SYSTEM* GetSystem();
	};

//--------------------------------------------------------------------------------
template<class T_SYSTEM>
class CTypedThreadPoolSubSystem : public CThreadPoolSubSystem
	{
	private:
		T_SYSTEM* m_pSystem;

	public:
		CTypedThreadPoolSubSystem(T_SYSTEM* = NULL);
		virtual ~CTypedThreadPoolSubSystem();

		T_SYSTEM* GetSystem();
	};

//--------------------------------------------------------------------------------
template<class T_SYSTEM>
inline CTypedSubSystem<T_SYSTEM>::CTypedSubSystem(T_SYSTEM* pSys)
	: CSubSystem((CSystem*) pSys), m_pSystem(pSys) {}

template<class T_SYSTEM>
inline CTypedSubSystem<T_SYSTEM>::~CTypedSubSystem() {}

template<class T_SYSTEM>
inline T_SYSTEM* CTypedSubSystem<T_SYSTEM>::GetSystem() { return m_pSystem; }

//--------------------------------------------------------------------------------
template<class T_SYSTEM>
inline CTypedThreadPoolSubSystem<T_SYSTEM>::CTypedThreadPoolSubSystem(T_SYSTEM* pSys)
	: CThreadPoolSubSystem((CSystem*) pSys), m_pSystem(pSys) {}

template<class T_SYSTEM>
inline CTypedThreadPoolSubSystem<T_SYSTEM>::~CTypedThreadPoolSubSystem() {}

template<class T_SYSTEM>
inline T_SYSTEM* CTypedThreadPoolSubSystem<T_SYSTEM>::GetSystem() { return m_pSystem; }

//--------------------------------------------------------------------------------
inline LONG CThreadPoolSubSystem::GetBusyThreadCount() { return m_nBusyThreadCount; }
inline void CThreadPoolSubSystem::IncBusyThreadCount() { ::InterlockedIncrement(&m_nBusyThreadCount); }
inline void CThreadPoolSubSystem::DecBusyThreadCount() { ::InterlockedDecrement(&m_nBusyThreadCount); }

#endif // !defined(AFX_SUBSYSTEM_H__9F10BA2A_835B_11D3_B0D3_00A0CC271D0D__INCLUDED_)
