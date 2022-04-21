objects = pdadd.o pdlist.o pdshow.o pdremove.o pd.o
executable = pdadd.exe pdlist.exe pdshow.exe pdremove.exe

all: $(objects)
	g++ pdadd.o pd.o -o pdadd.exe
	g++ pdlist.o pd.o -o pdlist.exe
	g++ pdshow.o pd.o -o pdshow.exe
	g++ pdremove.o pd.o -o pdremove.exe

pd.o: pd.h pd.cpp
	g++ -g -c pd.cpp

pdadd: pd.o pdadd.cpp
	g++ -g pdadd.cpp pd.o -o pdadd.exe 

pdlist: pd.o pdlist.cpp
	g++ -g pdlist.cpp pd.o -o pdlist.exe

pdshow: pd.o pdshow.cpp
	g++ -g pdshow.cpp pd.o -o pdshow.exe

clean:
	rm $(objects) $(executable)