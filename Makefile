all: fraction.cpp fraction.h sample.cpp
	g++ -std=c++17 fraction.cpp sample.cpp -o sample.exe

sample: fraction.o sample.cpp
	g++ -std=c++17 -g fraction.o sample.cpp -o sample.exe

fraction.o: fraction.h fraction.cpp
	g++ -std=c++17 -g -c fraction.cpp

clean:
	del /s *.exe *.o