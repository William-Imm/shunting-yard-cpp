CC=clang++

CFLAGS=-c -Wall -std=c++11

all: rpn_evaluate

rpn_evaluate: equation.o main.o utility.o
	$(CC) equation.o main.o utility.o -o rpn_evaluate

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm *.o rpn_evaluate
