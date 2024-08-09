.PHONY: all clean debug

SRCS=$(wildcard *.c)
BINS=$(patsubst %.c,%,$(SRCS))

CXXFLAGS=-O3 -Wall -Wextra -Werror -Wconversion -std=c++20

all: $(BINS)

test: polymorphism.cpp main.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf test

debug:
	echo "SRCS=$(SRCS)"
	echo "BINS=$(BINS)"
