CC = g++
PROG = runaway
D = src/

all: $(PROG) clean

$(PROG): $(D)main.cpp fileio.o path.o board.o step.o
	$(CC) -o $(PROG).exe $(D)main.cpp $(D)fileio.o $(D)path.o $(D)board.o $(D)step.o

fileio.o: $(D)fileio.cpp
	$(CC) -c -o $(D)fileio.o $(D)fileio.cpp

path.o: $(D)path.cpp step.o
	$(CC) -c -o $(D)path.o $(D)path.cpp $(D)step.o

step.o: $(D)step.cpp
	$(CC) -c -o $(D)step.o $(D)step.cpp

board.o: $(D)board.cpp $(D)path.o
	$(CC) -c -o $(D)board.o $(D)board.cpp $(D)path.o

clean:
	rm -f *.o *~ \#* $(D)*.o $(D)*~ $(D)\#*
