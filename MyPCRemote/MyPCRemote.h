
// MyPCRemote.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "IniFile.h"

// CMyPCRemoteApp:
// See MyPCRemote.cpp for the implementation of this class
//

class CMyPCRemoteApp : public CWinApp
{
public:
	CIniFile	m_IniFile;
	CMyPCRemoteApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMyPCRemoteApp theApp;