CC=clang++

CFLAGS=-c -g -Wall -std=c++11 -I/usr/include/SDL2

all: rpn_evaluate gui

gui: equation.o gui.o utility.o varequation.o
	$(CC) equation.o gui.o utility.o varequation.o -o gui -lSDL2 -lGL -lGLU

rpn_evaluate: equation.o main.o utility.o varequation.o
	$(CC) equation.o main.o utility.o varequation.o -o rpn_evaluate

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o rpn_evaluate gui
