//--------------------------------------------------------------------------------
//
// Copyright (c) 1999 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

// MCImageLibTr.h: interface for the CMCImageLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MCSPLIT_H__C01FB4E0_33B2_11D3_87C7_00104B9E6286__INCLUDED_)
#define AFX_MCSPLIT_H__C01FB4E0_33B2_11D3_87C7_00104B9E6286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <result.h>
#include <MCImageLibGlobals.h>

//--------------------------------------------------------------------------------
class CMCImageLibBreakParam : public MC_BREAK_BLOCK
	{
	public:
		CMCImageLibBreakParam() { PMC_BREAK_BLOCK_INIT(this); }
	};

//--------------------------------------------------------------------------------
class CMCImageLibParam : public MC_IMAGELIB_BLOCK
	{
	public:
		CMCImageLibParam() { PMC_IMAGELIB_BLOCK_INIT(this); }
	};

//--------------------------------------------------------------------------------
class CMCImageLib : public CResult
	{
	public:
		CMCImageLib();
		virtual ~CMCImageLib();

	private:
		static HINSTANCE m_hInst;
		static MCIMAGELIB m_pMCImageLib;
		static int m_nRefCount;

	public:
		bool ImageLibCall(CMCImageLibParam&);
		bool SplitMergeFile(int nCmd, DCM_HEADER*, LPCTSTR pFilename, LPCTSTR pSourceDir, LPCTSTR pDestDir);

		bool SplitFile(DCM_HEADER* pHeader, LPCTSTR pFilename, LPCTSTR pSourceDir = NULL, LPCTSTR pDestDir = NULL)
			{ return SplitMergeFile(MC_IMAGELIB_BREAK, pHeader, pFilename, pSourceDir, pDestDir); }

//		bool MergeFile(LPCTSTR pFilename, LPCTSTR pSourceDir = NULL, LPCTSTR pDestDir = NULL)
//			{ return SplitMergeFile(MC_IMAGELIB_REPAIR, NULL, pFilename, pSourceDir, pDestDir); }
		bool MergeFile(LPCTSTR pFilename, LPCTSTR pSourceDir = NULL, LPCTSTR pDestDir = NULL);
	};

#endif // !defined(AFX_MCSPLIT_H__C01FB4E0_33B2_11D3_87C7_00104B9E6286__INCLUDED_)
