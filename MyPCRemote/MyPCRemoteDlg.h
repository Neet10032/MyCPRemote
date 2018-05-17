
// MyPCRemoteDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "TrueColorToolBar.h"

// CMyPCRemoteDlg dialog
class CMyPCRemoteDlg : public CDialogEx
{
// Construction
public:
	CMyPCRemoteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYPCREMOTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CStatusBar m_wndStatusBar;
	int m_iPCCount;
	CTrueColorToolBar m_MainToolBar;
	NOTIFYICONDATA m_NotifyIconData;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CList_Online;
	CListCtrl m_CList_Log;
	int m_iWidthOfListOnline;
	int m_iWidthOfListLog;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void InitListControlor();
	void InitMenu();
	int GetWidthOfListOnLine();
	int GetWidthOfListLog();
	void AddOnlinePc(CString strIP, CString strAddr, CString strPCName, CString strOS, CString strCPU, CString strCamera, CString strPing);
	void DeleteOnlinePc(int iItem);
	void AddNewLog(bool bIsOk, CString strMsg);
	void Test(); // 测试功能使用
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMRClickListOnline(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOnlineManagecmd();
	afx_msg void OnOnlineManagedesktop();
	afx_msg void OnOnlineManagefile();
	afx_msg void OnOnlineManageprocess();
	afx_msg void OnOnlineManageregistry();
	afx_msg void OnOnlineManageserver();
	afx_msg void OnOnlineManagevoice();
	afx_msg void OnOnlineManagewindows();
	afx_msg void OnMainFileClose();
	afx_msg void OnMainHelpAbout();
	afx_msg void OnMainSettingGener();
	void CreateStatusBar();
	void UpdataWindowSize();
	afx_msg void OnOnlineOffline();
	void CreateMainToolBar();
	afx_msg void OnOnlineManagecamero();
	afx_msg void OnMainSettingGenServerside();
	afx_msg void OnMainSettingSetupparameters();
	void CreateNotifyIcon();
protected:
	afx_msg LRESULT OnUmIconnotify(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnNotifyShow();
	afx_msg void OnNotifyExit();
//	afx_msg void OnDropFiles(HDROP hDropInfo);
};





