// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPCRemote.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg dialog

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
{
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
	DDX_Text(pDX, IDC_EDIT_MAXCONNECTION, m_iMaxConnection);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSettingDlg message handlers


void CSettingDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	((CMyPCRemoteApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "ListenPort", m_iPort);
	((CMyPCRemoteApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "MaxConnection", m_iMaxConnection);
	MessageBox("The setting is successful and the restart takes effect");
	CDialogEx::OnOK();
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_iPort = ((CMyPCRemoteApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "ListenPort");
	m_iMaxConnection = ((CMyPCRemoteApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "MaxConnection");
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
