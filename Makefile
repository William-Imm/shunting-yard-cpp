CC=clang++
UNAME_S=$(shell uname -s)

CXXFLAGS=-c -g -Wall -std=c++11 -I/usr/include/SDL2 -I/usr/local/include/SDL2
LDFLAGS=
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -framework SDL2
else
	LDFLAGS += -lSDL2 -lGL
endif

all: rpn_evaluate gui

gui: equation.o gui.o utility.o varequation.o
	$(CC) $(LDFLAGS) -o $@ $+

rpn_evaluate: equation.o main.o utility.o varequation.o
	$(CC) -o $@ $+

%.o: %.cpp
	$(CC) $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o rpn_evaluate gui
