CC=g++
CXXFLAGS=-g -std=c++11 -Wall
SOURCE=listTest.cpp entry_list.cpp main_list.cpp operation.cpp
DEPS=entry_list.hpp main_list.hpp operation.hpp
EXECUTABLE=testList

target:
	$(CC) $(SOURCE) -o $(EXECUTABLE)

