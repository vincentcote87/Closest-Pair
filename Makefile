# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -std=c++11


all: bruteforce create divideconquer

bruteforce: bruteforce.cpp
	$(CC) $(CFLAGS) -o bruteforce bruteforce.cpp

divideconquer: divideconquer.cpp
	$(CC) $(CFLAGS) -o divideconquer divideconquer.cpp

create: create.cpp
	$(CC) $(CFLAGS) -o create create.cpp

clean:
	$(RM) *.o create divideconquer bruteforce

clean-points:
	$(RM) ./pointsData/*.txt

clean-all: clean clean-points

