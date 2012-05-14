// wifi-keep-alive/winmain.cpp
//
//		*Contains the entry point for the program and logic for the
//			visible window
//								(c) Zach Hedges 2012


#include "winmain.h"
#include "wifi-keep-alive.h"
#include "resource.h"

HWND hList = NULL;
extern PingMonitor* pm;
UINT_PTR delTimer;

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_TIMER:
			KillTimer(NULL, delTimer);
			pm->CheckFrame();
			break;
		case WM_INITDIALOG:
			hList = GetDlgItem(hwnd, IDC_EDIT);
			pm = new PingMonitor(hList, hwnd);
			
			SendMessage(hList, EM_SETLIMITTEXT, 100, 0);
			SetDlgItemText(hwnd, addressinput, "google.com");
			SetDlgItemText(hwnd, IDC_EDIT, "wifi-keep-alive is ready. Enter an IP address to monitor and click Start.");
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_BUTTONSTART:{
				
					// get the URL from the address box to construct our pingmonitor
					LPTSTR url[GetWindowTextLength(hList)+1];
					GetDlgItemText(hwnd, IDC_EDIT, *url, sizeof(url));

					// tell the user we're starting the operation, and disable the
					// address box + start button
					SetDlgItemText(hwnd, IDC_EDIT, "Starting...");
					
					
					//into the loop we go
					pm->Start(reinterpret_cast<const char*>(url));
					break;
				}
				case IDC_BUTTONSTOP:{
					pm->Stop();
					if (pm != NULL) delete pm;
					break;
				}
			}
			break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
			break;
		default:
			return FALSE;
		
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(mydialog), NULL, DlgProc);
}
