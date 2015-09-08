CXX?=	g++
CXXFLAGS?=$(shell pkg-config sdl2 --libs --cflags) -std=c++11
SRC =	\
		Caomps.cpp \
		display.cpp \
		main.cpp \

#${CXX}
all:
	clang++ -O3 $(SRC) ${CXXFLAGS} -o main

small:
	${CXX} -Os $(SRC) ${CXXFLAGS} -o main
	strip main
	sstrip main

debug:
	${CXX} -O0 -g $(SRC) ${CXXFLAGS} -o main

run:
	@echo --- C++11 ---
	./main

clean:
	rm -f main
