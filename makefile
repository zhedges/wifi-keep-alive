wifi-keep-alive: objs
	g++ winmain.o resource.o -mwindows -O3 -Wall -o wifi-keep-alive.exe

objs: res
	g++ -c -O3 -Wall winmain.cpp

res: resource.rc resource.h
	windres resource.rc resource.o
	
clean:
	rm -f *.o *.exe