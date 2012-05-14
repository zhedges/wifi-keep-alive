#ifndef HEADER_WIFI_KEEP_ALIVE
#define HEADER_WIFI_KEEP_ALIVE

#include <string>
#include <queue>
#include <windows.h>

class PingMonitor
{
	public:
		PingMonitor();
		PingMonitor(HWND editCtrl, HWND dialog);
		std::string GetUrl();
		void Start(std::string pingURL);
		void Stop();
		void CheckFrame();
		
	private:
		HWND _edit, _dlg;
		std::string _cmd, _url;
		std::queue<std::string> _input;
};

#endif//HEADER_WIFI_KEEP_ALIVE