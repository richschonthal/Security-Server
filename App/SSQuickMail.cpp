//--------------------------------------------------------------------------------
//
// Copyright (c) 2000 @COMPANY
//
// Programming by Rich Schonthal
//
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "SSQuickMail.h"
#include "SSConfigGeneral.h"
#include "SSConfigBackup.h"

//--------------------------------------------------------------------------------
CSSQuickMail::CSSQuickMail()
	{
	CSSConfigGeneral config;
	m_sIP = config.m_sEmailIP;
	m_sFrom = config.m_sEmailFrom;
	m_sTo = config.m_sEmailTo;
	CSSConfigBackup config2;
	if(config2.m_bIsBackup)
		m_sFrom += " Bkup";
	}

//--------------------------------------------------------------------------------
bool CSSQuickMail::Send()
	{
	CSSConfigGeneral config;
	if(config.m_bNoEmail)
		return false;
	CString sTemp;
	sTemp.Format("Server Addr: %s\r\nServer Port: %d\r\n", (LPCTSTR) config.m_sMainIP, config.m_nMainPort);
	CString sLine('-', 40);
	if(m_sMsg.Right(2) != "\r\n")
		m_sMsg += "\r\n";
	m_sMsg += sLine + "\r\n" + sTemp;
	return CQuickMail::Send();
	}
