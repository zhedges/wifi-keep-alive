CXX=g++
CXXFLAGS=-O3 -Wall
objs=winmain.o resource.o

wifi-keep-alive.exe: $(objs)
	$(CXX) -mwindows $(CXXFLAGS) -o wifi-keep-alive.exe $(objs)

winmain.o: winmain.h resource.h
resource.o: resource.rc resource.h
	windres resource.rc resource.o
	
.PHONY: clean
clean:
	rm -f *.o *.exe