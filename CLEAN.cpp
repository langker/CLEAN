#include <windows.h>
#include "resource.h"
#include <string.h>
HICON g_hIcon = NULL;
HANDLE hThread=NULL;
DWORD WINAPI code(LPVOID pParam);
BOOL WINAPI DlgProcMain(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{

	g_hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);

	
	int nResult = DialogBoxParam(hInstance,(LPCTSTR)IDD_DIALOG1,NULL,DlgProcMain,NULL);
	return 0;
}

BOOL WINAPI DlgProcMain(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	int g=0;
	switch(msg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_CLEAN:
			
			SetTimer(hwnd,1,500,NULL);
			::EnableWindow(::GetDlgItem(hwnd, IDC_CLEAN), FALSE);
		    hThread=CreateThread(NULL,0,code,NULL,0,0);
			WaitForSingleObject(hThread,INFINITE);
			::SetWindowText(GetDlgItem(hwnd,IDC_STATIC1),"清理完毕！");
			::EnableWindow(::GetDlgItem(hwnd, IDC_CLEAN), TRUE);
			KillTimer(hwnd,1);
            break;
		case IDC_ABOUT:
			MessageBox(hwnd,"langker个人作品\n\n第一次不用MFC\n真爽啊！","CLEAN",0);
		}
		break;
	case WM_INITDIALOG:
		{
		SendMessage(hwnd, WM_SETICON,ICON_BIG,(long)g_hIcon);
		SendMessage(hwnd, WM_SETICON,ICON_SMALL,(long)g_hIcon);
		break;
		}
	case WM_TIMER:
		{
			switch(g)
			{
			case 0:
				::SetWindowText(GetDlgItem(hwnd,IDC_STATIC1),"开始清理，请等待...");break;
			case 1:
				::SetWindowText(GetDlgItem(hwnd,IDC_STATIC1),"开始清理，请等待...");break;
			case 2:
				::SetWindowText(GetDlgItem(hwnd,IDC_STATIC1),"开始清理，请等待...");break;
			}
			g++;
			if(g==3)
			{
				g=0;
			}
			break;
		}
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return 0;
}
DWORD WINAPI code(LPVOID pParam)
{   
	int i=0;
	char code[][100]={"del /f /s /q %systemdrive%\*.tmp",
		"del /f /s /q %systemdrive%\*._mp ",
		"del /f /s /q %systemdrive%\*.log ",
		"del /f /s /q %systemdrive%\*.gid ",
		"del /f /s /q %systemdrive%\*.chk ",
		"del /f /s /q %systemdrive%\*.old ",
		"del /f /s /q %systemdrive%\recycled\*.* ",
		"del /f /s /q %windir%\*.bak ",
		"del /f /s /q %windir%\prefetch\*.* ",
		//"rd /s /q %windir%\temp & md %windir%\temp ",
		"del /f /q %userprofile%\cookies\*.* ",
		"del /f /q %userprofile%\recent\*.* ",
		"del /f /s /q \"%userprofile%\Local Settings\Temporary Internet Files\*.*\" ",
		"del /f /s /q \"%userprofile%\Local Settings\Temp\*.* \" ",
		"del /f /s /q \"%userprofile%\recent\*.*\"  " };
	for(i=0;i<14;i++)
		WinExec(code[i],0);
	return 0;
}