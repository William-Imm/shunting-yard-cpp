CXX=c++
UNAME_S=$(shell uname -s)

CXXFLAGS=-c -g -Wall -std=c++11
LDFLAGS=
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -framework SDL2 -framework OpenGL
else
	LDFLAGS += -lSDL2 -lGL
endif

all: rpn_evaluate gui

gui: equation.o gui.o utility.o varequation.o
	$(CXX) $(LDFLAGS) -o $@ $+

rpn_evaluate: equation.o main.o utility.o varequation.o
	$(CXX) -o $@ $+

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o rpn_evaluate gui
