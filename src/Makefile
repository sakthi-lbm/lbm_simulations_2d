CPP_COMPILE = g++
FLAGS = -Wall -O3

EXECUTABLE = lbm
SRC = $(wildcard *.cpp)

all:
	$(CPP_COMPILE) $(FLAGS) $(SRC) -o $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
