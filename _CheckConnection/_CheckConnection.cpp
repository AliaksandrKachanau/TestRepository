// _CheckConnection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "_CheckConnection.h"
#include "MetaConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

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

			string host;
			string login;
			string password;
			string userlogin;
			char buffer[MAX_PATH] = "";
			GetCurrentDirectory(MAX_PATH, buffer);
			ifstream infile("settings.txt"); 
			if (infile.is_open())  
			{
				infile >> host >> login >> password;
			}
			else
			{
				cout<<"Can't open file settings.txt in "<<buffer;
				getch();
				return 0;
			}
			infile.close();
			CMetaConnect Meta(host, atoi(login.c_str()), password);
			while (1)
			{
				Meta.CheckConnection();
				Sleep(500);
			}
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
