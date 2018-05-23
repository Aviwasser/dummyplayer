# A generic makefile for running single-file C++ projects.
#
# AUTHOR: Erel Segal-Halevi

CXX=clang++-5.0
RM=rm -f
CPPFLAGS=-std=c++17 

ifndef MAIN
  MAIN=./main.cpp
endif

SOURCES=$(MAIN)

all: 
	$(CXX) $(CPPFLAGS) *.cpp
	./a.out

clean:
	$(RM) *.exe a.out *.class
