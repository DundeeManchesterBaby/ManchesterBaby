#The Compiler we'll be using
GPP = g++

#The flags we'll be passing to the compiler
CFLAGS= -g -Wall -Wextra -pedantic -std=c++11

#The default build goal, running 'make' will run 'make all'
.DEFAULT_GOAL

all: $(wildcard *.cpp)
	($GPP) $(CFLAGS) $(wildcard *.cpp)  

