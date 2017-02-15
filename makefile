CXX=g++
GL_FLAGS=-lGL -lglfw -ldl
CXX_FLAGS=-std=c++14 -O2 -fdiagnostics-color=always
DEBUG_FLAGS=-Wall -Wno-unused-parameter -Wshadow -Wextra -pedantic -g

SRCS=$(shell find src -name "*.cpp")
OBJS=$(patsubst src/%.cpp,obj/%.o, $(SRCS))

obj/%.o: src/%.cpp src/%.hpp src/globals.hpp
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

game: $(OBJS) main.cpp include/glad.c
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) -o $@ $^ $(GL_FLAGS)
	
.PHONY: clean run test

clean:
	rm -f obj/*.o game
	
run: game
	./game

test: game
	gdb -q game
