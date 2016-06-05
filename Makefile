CC=clang++

CFLAGS=-c -Wall -std=c++11

all: rpn_evaluate

rpn_evaluate: convert.o evaluate.o main.o
	$(CC) convert.o evaluate.o main.o -o rpn_evaluate

convert.o: convert.cpp
	$(CC) $(CFLAGS) convert.cpp

evaluate.o: evaluate.cpp
	$(CC) $(CFLAGS) evaluate.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm *.o rpn_evaluate
