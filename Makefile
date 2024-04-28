.PHONY: all clean

CXXFLAGS=-O3 -Wall -Wextra -Werror -Wconversion -std=c++20

all: test

test: polymorphism.cpp main.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf test
