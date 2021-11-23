LIBS= -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lGL -lpthread -ldl -lX11 -ludev -lXcursor -lXrandr -lfreetype
# CXXFLAGS= -ggdb -std=c++20
CXXFLAGS= -O3 -std=c++20

all: clean build
clean:
	rm -f stetris
build:
	g++ src/* ${CXXFLAGS} ${LIBS} -o stetris
