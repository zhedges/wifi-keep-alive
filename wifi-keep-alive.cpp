#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "wifi-keep-alive.h"
#include "resource.h"

using std::cin; using std::cout; using std::endl;
using std::string;
using std::queue;

// Global variables
PingMonitor* pm = NULL;
extern UINT_PTR delTimer;

PingMonitor::PingMonitor() {}

PingMonitor::PingMonitor(HWND editCtrl, HWND dialog): _edit(editCtrl), _dlg(dialog)
{

}

std::string PingMonitor::GetUrl()
{
	return _url;
}

void PingMonitor::CheckFrame()
{	// this function processes one line of input from our process and
	// chucks it in the edit control
	
	//do stuff
	
	//create a timer that will let us repeat this function without
	//blocking when it dies
	if((delTimer = SetTimer(NULL, 0, 80, NULL)) == 0)
	PostQuitMessage(-1);
}

void PingMonitor::Start(std::string pingURL)
{	
	_url = pingURL;
	_cmd = "ping -t " + pingURL;
	
	//start crazy weird loop of doom
	CheckFrame();
}

void PingMonitor::Stop()
{

}

/*
int pingLoop()
{	
		//read a line from input and put it in the queue
		q.push(str_temp);
		
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
	return 0;
} */