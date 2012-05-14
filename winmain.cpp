#include <iostream>
#include <string>
#include <queue>
#include <windows.h>

#include "winmain.h"
#include "resource.h"

using std::cin; using std::cout; using std::endl;
using std::string; using std::queue;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_LBUTTONDOWN: {
			char szFileName[MAX_PATH];
			HINSTANCE hInstance = GetModuleHandle(NULL);
			GetModuleFileName(hInstance, szFileName, MAX_PATH);
			MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			EndPaint(hwnd, &ps);
			break;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	LPCSTR AppTitle = "WiFi KeepAlive";
	
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	wcex.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH) COLOR_WINDOWFRAME;
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
	wcex.lpszClassName = AppTitle;
	
	if (!RegisterClassEx(&wcex))
		return 0;
	
	HWND hwnd = CreateWindowEx(0,
					AppTitle, AppTitle,	
					WS_OVERLAPPEDWINDOW,
					
					CW_USEDEFAULT, CW_USEDEFAULT,
					640, 480,
					
					NULL, NULL,	hInstance, NULL );
		
	if (hwnd == NULL)
	{
		return 0;
	}
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	// Run the message loop.
	
	MSG msg;
	BOOL bRet;
	while ( (bRet = GetMessage(&msg, NULL, 0, 0)) > 0)
	{
		if(bRet == -1)
		{
			// error!
			PostQuitMessage(-2);
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}


int pingLoop(int argc, char** argv)
{
	
	// we are going to keep track of our input with a queue.
	string in;
	queue<string> q;
	
	// loop on stdin
	//while(getline(cin,in))
	//{	
		//read a line from input and put it in the queue
		//getline(cin,in);
		q.push(in);
		
		//while there is data in teh queue, display it
		while(!q.empty()){
			
			//examine the next input message in the queue
			if(q.front() == "Request timed out.") //symptom of problem
			{
				// call our input synthesizing function here
				cout << prefix << "Connection lost, let's try and restart it..." << endl;
			} 
		else if(q.front() == "General failure.")
			{
				cout << prefix << "LAN cable disconnected or adapter failure." << endl;
			}
		else if(q.front().substr(0,10) == "Reply from") //a packet came back
			{
				string tmp = q.front().substr( q.front().rfind("time=") + 5,
											   (q.front().rfind("TTL") - (q.front().rfind("time=") + 5))
											 );
				cout << prefix << "Ping: " << tmp << endl;
			}
		else if(q.front().substr(0,12) == "Ping request") // DNS lookup failed
			{
				cout << "[ERROR] DNS lookup failed, exiting." << endl;
				break;
			}
			else
			{
				cout << q.front() << endl;
			}
			q.pop();
		}
		
	//}
return 0;
}