CXX = g++
CXXFLAGS = -std=c++1z -O2
INC = -I ./src
SRC = ./src/rational.cpp 

default:
	$(CXX) $(CXXFLAGS) $(INC) $(SRC) main.cpp -o main

unit_tests:
	$(CXX) $(CXXFLAGS) $(INC) $(SRC) ./test/unit_tests.cpp -lgtest -o unit_tests
	./unit_tests
	rm unit_tests
