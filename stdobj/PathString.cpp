//--------------------------------------------------------------------------------
//
// Copyright (c) 1999 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

// PathString.cpp: implementation of the CPathString class.
//
//////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
#include "stdafx.h"
#include "PathString.h"

//--------------------------------------------------------------------------------
#pragma comment(lib, "Shlwapi.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
-PathAppend
PathCanonicalize
PathCompactPath
PathCompactPathEx
-PathCommonPrefix
PathFindOnPath
-PathGetCharType
-PathIsContentType
-PathIsHTMLFile
-PathMakePretty
-PathMatchSpec
PathParseIconLocation
-PathQuoteSpaces
-PathRelativePathTo
-PathRemoveArgs
-PathRemoveBlanks
-PathRemoveExtension
-PathRemoveFileSpec
-PathRenameExtension
PathSearchAndQualify
PathSetDlgItemPath
-PathUnquoteSpaces
*/

//--------------------------------------------------------------------------------
CPathString::CPathString(const CString sNew)
		: CString(sNew)
	{

	}

//--------------------------------------------------------------------------------
CPathString::CPathString(LPCTSTR pNew)
		: CString(pNew)
	{

	}

//--------------------------------------------------------------------------------
CPathString::~CPathString()
	{

	}

//--------------------------------------------------------------------------------
bool CPathString::Append(LPCTSTR pMore)
	{
	size_t nLen = GetLength() + _tcslen(pMore) + 8;
	BOOL bRv = ::PathAppend(GetBuffer((int) nLen), pMore);
	ReleaseBuffer();
	return bRv != 0;
	}

//--------------------------------------------------------------------------------
int CPathString::CommonPrefix(LPCTSTR pFile, CPathString& sDest)
	{
	size_t nRv = ::PathCommonPrefix((LPCTSTR) this, pFile, sDest.GetBuffer((int)_tcslen(pFile)+1));
	sDest.ReleaseBuffer((int)nRv);
	return (int)nRv;
	}

//--------------------------------------------------------------------------------
CPathString::ECharTypes CPathString::GetCharType(_TUCHAR ch)
	{
	return (ECharTypes) ::PathGetCharType(ch);
	}

//--------------------------------------------------------------------------------
bool CPathString::IsContentType(LPCTSTR pContentType)
	{
	return ::PathIsContentType((LPCTSTR) this, pContentType) != 0;
	}

//--------------------------------------------------------------------------------
bool CPathString::IsHTMLFile()
	{
//	return ::PathIsHTMLFile((LPCTSTR) this) != 0;
	return false;
	}

//--------------------------------------------------------------------------------
bool CPathString::MakePretty()
	{
	BOOL bRv = ::PathMakePretty(GetBuffer(1));
	ReleaseBuffer();
	return bRv != 0;
	}

//--------------------------------------------------------------------------------
bool CPathString::MatchSpec(LPCTSTR pSpec)
	{
	return ::PathMatchSpec((LPCTSTR) this, pSpec) != 0;
	}

//--------------------------------------------------------------------------------
void CPathString::QuoteSpaces()
	{
	int nLen = GetLength();
	nLen += (sizeof('"') * 2);
	::PathQuoteSpaces(GetBuffer(nLen));
	ReleaseBuffer();
	}

//--------------------------------------------------------------------------------
bool CPathString::RelativePathTo(LPCTSTR pFrom, DWORD nAttrFrom, LPCTSTR pTo, DWORD nAttrTo)
	{
	BOOL bRv = ::PathRelativePathTo(GetBuffer(MAX_PATH + 1), pFrom, nAttrFrom, pTo, nAttrTo);
	ReleaseBuffer();
	return bRv != 0;
	}

//--------------------------------------------------------------------------------
void CPathString::RemoveArgs()
	{
	::PathRemoveArgs(GetBuffer(1));
    ReleaseBuffer();
    }

//--------------------------------------------------------------------------------
void CPathString::RemoveBlanks()
	{
	::PathRemoveBlanks(GetBuffer(1));
    ReleaseBuffer();
	}

//--------------------------------------------------------------------------------
void CPathString::RemoveExtension()
	{
	::PathRemoveExtension(GetBuffer(1));
    ReleaseBuffer();
	}

//--------------------------------------------------------------------------------
void CPathString::RemoveFileSpec()
	{
	::PathRemoveFileSpec(GetBuffer(1));
    ReleaseBuffer();
	}

//--------------------------------------------------------------------------------
bool CPathString::RenameExtension(LPCTSTR pExt)
	{
	BOOL bRv = ::PathRenameExtension(GetBuffer(MAX_PATH+1), pExt);
	ReleaseBuffer();
	return bRv != 0;
	}

//--------------------------------------------------------------------------------
void CPathString::UnquoteSpaces()
	{
	::PathUnquoteSpaces(GetBuffer(1));
	ReleaseBuffer();
	}

//--------------------------------------------------------------------------------
CString CPathString::GetExtension()
	{
	int nIndex = ReverseFind('.');
	CString sTemp;

	if(nIndex != -1)
		sTemp = Mid(nIndex);

	return sTemp;
	}

//--------------------------------------------------------------------------------
CString CPathString::GetPathnamePart(unsigned int nLevel)
	{
	CString sTemp;
	int nIndex = -1;
	for(int i = 0; i != nLevel && nIndex != -1; i++)
		nIndex = Find('\\', nIndex + 1);
	if(nIndex == nLevel)
		{
		for(i = nIndex + 1; i < GetLength(); i++)
			{
			if(GetAt(i) == '\\')
				break;
			sTemp += GetAt(i);
			}
		}
	return sTemp;
	}

//--------------------------------------------------------------------------------
CString CPathString::GetPathnamePartReverse(unsigned int nLevel)
	{
	CString sTemp;
	int nCurLevel = -1;
	int i = GetLength() - 1;
	if(GetAt(i) == '\\')
		i--;
	for(; i >= 0 && nCurLevel != nLevel; i--)
		if(GetAt(i) == '\\')
			nCurLevel++;
	if(nCurLevel == nLevel)
		{
		for(i += 2; i < GetLength(); i++)
			{
			if(GetAt(i) == '\\')
				break;
			sTemp += GetAt(i);
			}
		}
	return sTemp;
	}

