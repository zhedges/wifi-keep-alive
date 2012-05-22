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
		bool setupChildProc();
		HWND _edit, _dlg;
		std::string _cmd, _url;
		std::queue<std::string> _input;
};

#endif//HEADER_WIFI_KEEP_ALIVE


//TODO: hardcode command string into setupchildproc.
// try to give the child process the WRITE END OF THE PIPE YOU DUMMY