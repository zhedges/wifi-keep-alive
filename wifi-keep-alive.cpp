#include <iostream>
#include <windows.h>
#include <queue>

#include "wifi-keep-alive.h"

using std::cout;
using std::cin;
using std::endl;

using std::string;

using std::queue;

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
}