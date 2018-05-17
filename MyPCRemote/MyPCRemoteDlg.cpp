
// MyPCRemoteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPCRemote.h"
#include "MyPCRemoteDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


LIST_COLUMN g_ListOnline[] = {
	{ "IP", 150 },
	{ "Address", 200 },
	{ "Name(PC)", 160 },
	{ "OS", 130 },
	{ "CPU", 80 },
	{ "Camera", 80 },
	{ "Ping", 80 }
};

LIST_COLUMN g_ListLog[] = {
	{ "Time", 150 },
	{ "Type", 200 },
	{ "Content", 750 },

};


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
//	afx_msg LRESULT OnUmIconnotify(WPARAM wParam, LPARAM lParam);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_MESSAGE(UM_ICONNOTIFY, &CAboutDlg::OnUmIconnotify)
END_MESSAGE_MAP()


// CMyPCRemoteDlg dialog



CMyPCRemoteDlg::CMyPCRemoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyPCRemoteDlg::IDD, pParent),
	m_iPCCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPCRemoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ONLINE, m_CList_Online);
	DDX_Control(pDX, IDC_LIST_LOG, m_CList_Log);
}

BEGIN_MESSAGE_MAP(CMyPCRemoteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ONLINE, &CMyPCRemoteDlg::OnNMRClickListOnline)
	ON_COMMAND(ID_ONLINE_MANAGECMD, &CMyPCRemoteDlg::OnOnlineManagecmd)
	ON_COMMAND(ID_ONLINE_MANAGEDESKTOP, &CMyPCRemoteDlg::OnOnlineManagedesktop)
	ON_COMMAND(ID_ONLINE_MANAGEFILE, &CMyPCRemoteDlg::OnOnlineManagefile)
	ON_COMMAND(ID_ONLINE_MANAGEPROCESS, &CMyPCRemoteDlg::OnOnlineManageprocess)
	ON_COMMAND(ID_ONLINE_MANAGEREGISTRY, &CMyPCRemoteDlg::OnOnlineManageregistry)
	ON_COMMAND(ID_ONLINE_MANAGESERVER, &CMyPCRemoteDlg::OnOnlineManageserver)
	ON_COMMAND(ID_ONLINE_MANAGEVOICE, &CMyPCRemoteDlg::OnOnlineManagevoice)
	ON_COMMAND(ID_ONLINE_MANAGEWINDOWS, &CMyPCRemoteDlg::OnOnlineManagewindows)
	ON_COMMAND(ID_MAIN_FILE_CLOSE, &CMyPCRemoteDlg::OnMainFileClose)
	ON_COMMAND(ID_MAIN_HELP_ABOUT, &CMyPCRemoteDlg::OnMainHelpAbout)
	ON_COMMAND(ID_MAIN_SETTING_GENER, &CMyPCRemoteDlg::OnMainSettingGener)
	ON_COMMAND(ID_ONLINE_OFFLINE, &CMyPCRemoteDlg::OnOnlineOffline)
	ON_COMMAND(ID_ONLINE_MANAGECAMERO, &CMyPCRemoteDlg::OnOnlineManagecamero)
	ON_COMMAND(ID_MAIN_SETTING_GEN_SERVERSIDE, &CMyPCRemoteDlg::OnMainSettingGenServerside)
	ON_COMMAND(ID_MAIN_SETTING_SETUPPARAMETERS, &CMyPCRemoteDlg::OnMainSettingSetupparameters)
	ON_MESSAGE(UM_ICONNOTIFY, &CMyPCRemoteDlg::OnUmIconnotify)
	ON_COMMAND(ID_NOTIFY_SHOW, &CMyPCRemoteDlg::OnNotifyShow)
	ON_COMMAND(ID_NOTIFY_EXIT, &CMyPCRemoteDlg::OnNotifyExit)
//	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMyPCRemoteDlg message handlers

BOOL CMyPCRemoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitListControlor();
	InitMenu();
	CreateStatusBar();
	AddNewLog(true, "MyPCRemote Start up");
	CreateMainToolBar();
	CreateNotifyIcon();
	UpdataWindowSize();
	AddNewLog(true, "MyPCRemote initializing complete");
#ifdef DEBUG
	Test();
#endif // DEBUG

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyPCRemoteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyPCRemoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyPCRemoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyPCRemoteDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (SIZE_MINIMIZED == nType)
	{
		return;
	}
	// TODO: Add your message handler code here
	if (m_CList_Online.m_hWnd)
	{
		CRect rect;
		rect.left = 1;
		rect.top = 80;
		rect.right = cx - 1;
		rect.bottom = cy*3/4 - 1;
		m_CList_Online.MoveWindow(rect);

		// 调整list空间每列宽度
		for (int i = 0; i < sizeof(g_ListOnline) / sizeof(g_ListOnline[0]); ++i){
			int iNewWidth = (cx - 4)*1.0*g_ListOnline[i].nWidth / m_iWidthOfListOnline;
			m_CList_Online.SetColumnWidth(i, iNewWidth);
		}
	}

	if (m_CList_Log.m_hWnd)
	{
		CRect rect;
		rect.left = 1;
		rect.top = cy*3/4 + 1;
		rect.right = cx - 1;
		rect.bottom = cy - 20;
		m_CList_Log.MoveWindow(rect);

		// 调整list空间每列宽度
		for (int i = 0; i < sizeof(g_ListLog) / sizeof(g_ListLog[0]); ++i){
			int iNewWidth = (cx-4)*1.0*g_ListLog[i].nWidth / m_iWidthOfListLog;
			m_CList_Log.SetColumnWidth(i, iNewWidth);
		}
	}

	if (m_wndStatusBar)
	{
		CRect rect;
		rect.left = 1;
		rect.top = cy - 20;
		rect.right = cx - 1;
		rect.bottom = cy - 1;
		m_wndStatusBar.MoveWindow(rect);
		m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_POPOUT, cx - 10);
	}

	if (m_MainToolBar.m_hWnd != NULL)              //工具条
	{
		CRect rc;
		rc.top = rc.left = 0;
		rc.right = cx;
		rc.bottom = 80;
		m_MainToolBar.MoveWindow(rc);     //设置工具条大小位置
	}
}



void CMyPCRemoteDlg::InitListControlor()
{
	// 设置列表风格
	m_CList_Online.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_CList_Log.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 初始化List表项目
	m_iWidthOfListOnline = 0;
	for (int i = 0; i < sizeof(g_ListOnline) / sizeof(g_ListOnline[0]); ++i){
		m_CList_Online.InsertColumn(i, g_ListOnline[i].psztitle, LVCFMT_CENTER, g_ListOnline[i].nWidth);
		m_iWidthOfListOnline += g_ListOnline[i].nWidth;
	}

	// 初始化List表项目
	m_iWidthOfListLog = 0;
	for (int i = 0; i < sizeof(g_ListLog) / sizeof(g_ListLog[0]); ++i){
		m_CList_Log.InsertColumn(i, g_ListLog[i].psztitle, LVCFMT_CENTER, g_ListLog[i].nWidth);
		m_iWidthOfListLog += g_ListLog[i].nWidth;
	}

}


void CMyPCRemoteDlg::InitMenu(){
	HMENU hMenu = ::LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU_MAIN));
	::SetMenu(this->GetSafeHwnd(), hMenu);                  //为窗口设置菜单
	::DrawMenuBar(this->GetSafeHwnd());                    //显示菜单
}


int CMyPCRemoteDlg::GetWidthOfListOnLine()
{
	return m_iWidthOfListOnline > 0 ? m_iWidthOfListOnline : 0;
}


int CMyPCRemoteDlg::GetWidthOfListLog()
{
	return m_iWidthOfListLog > 0 ? m_iWidthOfListLog : 0;
}


void CMyPCRemoteDlg::AddOnlinePc(CString strIP, CString strAddr, CString strPCName, CString strOS,CString strCPU, CString strCamera, CString strPing)
{
	m_CList_Online.InsertItem(0, strIP);
	m_CList_Online.SetItemText(0, ONLINE_LIST_ADDR, strAddr);
	m_CList_Online.SetItemText(0, ONLINE_LIST_COMPUTER_NAME, strPCName);
	m_CList_Online.SetItemText(0, ONLINE_LIST_OS, strOS);
	m_CList_Online.SetItemText(0, ONLINE_LIST_CPU, strCPU);
	m_CList_Online.SetItemText(0, ONLINE_LIST_VIDEO, strCamera);
	m_CList_Online.SetItemText(0, ONLINE_LIST_PING, strPing);

	AddNewLog(true, strIP + " Online");
}


void CMyPCRemoteDlg::DeleteOnlinePc(int iItem){

}


void CMyPCRemoteDlg::AddNewLog(bool bIsOK, CString strMsg){
	CString strIsOK, strTime;
	CTime t = CTime::GetCurrentTime();
	strTime = t.Format("%H:%M:%S");
	if (bIsOK)
	{
		strIsOK = "sucessful";
	}
	else{
		strIsOK = "fauil";
	}
	m_CList_Log.InsertItem(0, strTime);
	m_CList_Log.SetItemText(0, 1, strIsOK);
	m_CList_Log.SetItemText(0, 2, strMsg);

	CString strStatusMsg;
	if (strMsg.Find("Online") > 0)         //处理上线还是下线消息
	{
		m_iPCCount++;
	}
	else if (strMsg.Find("Offline") > 0)
	{
		m_iPCCount--;
	}
	else if (strMsg.Find("Disconnect") > 0)
	{
		m_iPCCount--;
	}
	m_iPCCount = (m_iPCCount <= 0 ? 0 : m_iPCCount);         //防止iCount 有-1的情况
	strStatusMsg.Format("连接:%d", m_iPCCount);
	m_wndStatusBar.SetPaneText(0, strStatusMsg);   //在状态条上显示文字
}


void CMyPCRemoteDlg::Test(){
	AddOnlinePc("192.168.0.1", "admin", "Lang", "Windows7", "2.2GHZ", "Yes", "123232");
	AddOnlinePc("192.168.0.2", "admin", "Lang", "Windows7", "2.2GHZ", "Yes", "123232");
	AddOnlinePc("192.168.0.3", "admin", "Lang", "Windows7", "2.2GHZ", "Yes", "123232");
}


void CMyPCRemoteDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnRButtonDown(nFlags, point);

	// do nothing
}


void CMyPCRemoteDlg::OnNMRClickListOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	CMenu	popup;
	popup.LoadMenu(IDR_MENU_ONLINE);
	CMenu*	pM = popup.GetSubMenu(0);
	CPoint	p;
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount();
	if (m_CList_Online.GetSelectedCount() == 0)       //如果没有选中
	{
		for (int i = 0; i < count; i++)
		{
			pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);          //菜单全部变灰
		}

	}

	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);

	*pResult = 0;
}


void CMyPCRemoteDlg::OnOnlineManagecmd()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManagecmd");
}


void CMyPCRemoteDlg::OnOnlineManagedesktop()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManagedesktop");
}


void CMyPCRemoteDlg::OnOnlineManagefile()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManagefile");
}


void CMyPCRemoteDlg::OnOnlineManageprocess()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManageprocess");
}


void CMyPCRemoteDlg::OnOnlineManageregistry()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManageregistry");
}


void CMyPCRemoteDlg::OnOnlineManageserver()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManageserver");
}


void CMyPCRemoteDlg::OnOnlineManagevoice()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManagevoice");
}


void CMyPCRemoteDlg::OnOnlineManagewindows()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManagewindows");
}


void CMyPCRemoteDlg::OnMainFileClose()
{
	// TODO: Add your command handler code here
	PostMessage(WM_CLOSE, 0, 0);
}


void CMyPCRemoteDlg::OnMainHelpAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CMyPCRemoteDlg::OnMainSettingGener()
{
	// TODO: Add your command handler code here
	MessageBox("OnMainSettingGener");
}


void CMyPCRemoteDlg::OnOnlineManagecamero()
{
	// TODO: Add your command handler code here
	MessageBox("OnOnlineManagecamero");
}


void CMyPCRemoteDlg::OnMainSettingGenServerside()
{
	// TODO: Add your command handler code here
	MessageBox("OnMainSettingGenServerside");
}


void CMyPCRemoteDlg::OnMainSettingSetupparameters()
{
	// TODO: Add your command handler code here
	MessageBox("OnMainSettingSetupparameters");
}



UINT g_indicators[] = {
		IDS_STRING_STATUSBAR
};


void CMyPCRemoteDlg::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this)
		|| !m_wndStatusBar.SetIndicators(g_indicators, sizeof(g_indicators) / sizeof(g_indicators[0]))){
		TRACE("Faild to create status bar\r\n");
		return;
	}
	CRect rc;
	::GetWindowRect(m_wndStatusBar.m_hWnd, rc);
	m_wndStatusBar.MoveWindow(rc);
}


void CMyPCRemoteDlg::UpdataWindowSize()
{
	// 产生WM_SIZE消息，以便初始List控件大小
	CRect rect;
	GetWindowRect(&rect);
	rect.bottom += 20;
	MoveWindow(rect);
}


void CMyPCRemoteDlg::OnOnlineOffline()
{
	// TODO: Add your command handler code here
	CString strIP;
	int iSelect = m_CList_Online.GetSelectionMark();
	strIP = m_CList_Online.GetItemText(iSelect, ONLINE_LIST_IP);
	m_CList_Online.DeleteItem(iSelect);
	strIP += " Offline";
	AddNewLog(true, strIP);
}


void CMyPCRemoteDlg::CreateMainToolBar()
{
	if (!m_MainToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_MainToolBar.LoadToolBar(IDR_TOOLBAR_MAIN))
	{
		TRACE0("Failed to create toolbar\n");
		return;      // fail to create
	}
	m_MainToolBar.ModifyStyle(0, TBSTYLE_FLAT);    //Fix for WinXP
	m_MainToolBar.LoadTrueColorToolBar
		(
		48,    //加载真彩工具条
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN
		);
	RECT rt, rtMain;
	GetWindowRect(&rtMain);
	rt.left = 0;
	rt.top = 0;
	rt.bottom = 80;
	rt.right = rtMain.right - rtMain.left + 10;
	m_MainToolBar.MoveWindow(&rt, TRUE);

	m_MainToolBar.SetButtonText(0, "Cmd");
	m_MainToolBar.SetButtonText(1, "Process");
	m_MainToolBar.SetButtonText(2, "Window");
	m_MainToolBar.SetButtonText(3, "Desktop");
	m_MainToolBar.SetButtonText(4, "File");
	m_MainToolBar.SetButtonText(5, "Voice");
	m_MainToolBar.SetButtonText(6, "Camera");
	m_MainToolBar.SetButtonText(7, "Service");
	m_MainToolBar.SetButtonText(8, "Registry");
	m_MainToolBar.SetButtonText(10, "Paramter");
	m_MainToolBar.SetButtonText(11, "Server Side");
	m_MainToolBar.SetButtonText(12, "Help");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}


void CMyPCRemoteDlg::CreateNotifyIcon()
{
	m_NotifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	m_NotifyIconData.hWnd = this->m_hWnd;
	m_NotifyIconData.uID = IDR_MAINFRAME;
	m_NotifyIconData.hIcon = m_hIcon;
	m_NotifyIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_NotifyIconData.uCallbackMessage = NULL;
	m_NotifyIconData.uCallbackMessage = UM_ICONNOTIFY;            //回调消息
	CString str = "MyPCRemote";       //气泡提示
	lstrcpyn(m_NotifyIconData.szTip, (LPCSTR)str, sizeof(m_NotifyIconData.szTip) / sizeof(m_NotifyIconData.szTip[0]));
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData);
}


//afx_msg LRESULT CAboutDlg::OnUmIconnotify(WPARAM wParam, LPARAM lParam)
//{
//
//	return 0;
//}


afx_msg LRESULT CMyPCRemoteDlg::OnUmIconnotify(WPARAM wParam, LPARAM lParam)
{
	switch ((UINT)lParam)
	{
	case WM_LBUTTONDOWN: // click or dbclick left button on icon
	case WM_LBUTTONDBLCLK: // should show desktop
		if (!IsWindowVisible())
			ShowWindow(SW_SHOW);
		else
			ShowWindow(SW_HIDE);
		break;
	case WM_RBUTTONDOWN: // click right button, show menu
		CMenu menu;
		menu.LoadMenu(IDR_MENU_NOTIFY);
		CPoint point;
		GetCursorPos(&point);
		SetForegroundWindow();
		menu.GetSubMenu(0)->TrackPopupMenu(
			TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
			point.x, point.y, this, NULL);
		PostMessage(WM_USER, 0, 0);
		break;
	}
	return 0;
}


void CMyPCRemoteDlg::OnNotifyShow()
{
	// TODO: Add your command handler code here
	ShowWindow(SW_SHOW);
}


void CMyPCRemoteDlg::OnNotifyExit()
{
	// TODO: Add your command handler code here
	PostMessage(WM_CLOSE);
}


//void CMyPCRemoteDlg::OnDropFiles(HDROP hDropInfo)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CDialogEx::OnDropFiles(hDropInfo);
//}
