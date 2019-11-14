CCC = g++
CCCFLAGS = -Wall -g -std=c++11 -lpthread
SRC = ./src/

all: main

main: main.o
    $(CCC) $(CCCFLAGS) $(SRC) $^ -o $@

%.o : %.cc
	$(CCC) -c $(CCCFLAGS) $<

clean:
	rm -f *.o *~ *% *# .#*

clean-all: clean
	rm -f main