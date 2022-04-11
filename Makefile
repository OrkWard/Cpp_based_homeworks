objects = pdadd.o pdlist.o pdshow.o pdremove.o 
executable = pdadd.exe pdlist.exe pdshow.exe pdremove.exe

all: $(objects)
	g++ -o pdadd.exe pdadd.o
	g++ -o pdlist.exe pdlist.o
	g++ -o pdshow.exe pdshow.o
	g++ -o pdremove.exe pdremove.o

pdadd.o pdlist.o pdshow.o pdremove.o: pd.h

*clean:
	rm $(objects) $(executable)