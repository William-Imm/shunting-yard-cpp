CC=clang++

CFLAGS=-c -Wall -std=c++11

all: rpn_evaluate

rpn_evaluate: convert.o evaluate.o main.o
	$(CC) convert.o evaluate.o main.o -o rpn_evaluate

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm *.o rpn_evaluate
