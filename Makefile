CC=clang++

CFLAGS=-c -g -Wall -std=c++11

all: rpn_evaluate

rpn_evaluate: equation.o main.o utility.o varequation.o
	$(CC) equation.o main.o utility.o varequation.o -o rpn_evaluate

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm *.o rpn_evaluate
