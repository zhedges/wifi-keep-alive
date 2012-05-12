#include <iostream>
#include <string>
#include <queue>
#include <windows.h>
#include "wifi-keep-alive.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	LPCSTR AppTitle = "WiFi KeepAlive";
	
	WNDCLASS wc;
	
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	= WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) COLOR_WINDOWFRAME;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = AppTitle;
	
	if (!RegisterClass(&wc))
		return 0;
	
	HWND hwnd = CreateWindow(
					AppTitle, AppTitle,	
					WS_OVERLAPPEDWINDOW,
					
					CW_USEDEFAULT, CW_USEDEFAULT,
					640, 480,
					
					NULL, NULL,	hInstance, NULL );
		
	if (hwnd == NULL)
	{
		return 1;
	}
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	// Run the message loop.
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
		
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			EndPaint(hwnd, &ps);
			return 0;
		}
		
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	// do we ever get here?
	return 0;
}

/*
int main(int argc, char** argv)
{
	
	// we are going to keep track of our input with a queue.
	string in;
	queue<string> q;
	
	// loop on stdin
	while(getline(cin,in))
	{	
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
		
	}
return 0;
} */