CXX?=g++
CXXFLAGS?=$(shell pkg-config sdl2 --libs --cflags) -std=c++11

all:
	${CXX} -O3 display.cpp ${CXXFLAGS} -o main

small:
	${CXX} -Os display.cpp ${CXXFLAGS} -o main
	strip main
	sstrip main

debug:
	${CXX} -O0 -g display.cpp ${CXXFLAGS} -o main

run:
	@echo --- C++11 ---
	./main

clean:
	rm -f main
