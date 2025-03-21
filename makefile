#Endrit Ngjelina COP 4530 U43630372
#this file is a makefile for project 1
#Makefile for linkedcalc and tester

#compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17

#target executable 
TARGET = linked_calc_test

#source file
SRC = tester.cpp linked_calc.cpp
OBJ = tester.o linked_calc.o

#header file
HEADERS = linked_calc.hpp

#target for program
all: $(TARGET)

#link object file and create executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

#compile tester.cpp to object file
tester.o: tester.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c tester.cpp

#linked_calc.cpp into object file
linked_calc.o: linked_calc.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c linked_calc.cpp

#clean target to remove files
clean:
	rm -f $(OBJ) $(TARGET)

#run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: clean all run
