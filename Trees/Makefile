CXX=g++
CXXFLAGS= -std=c++1z -O0 -g
INC= -I ./src

all:
	$(CXX) $(CXXFLAGS) $(INC) main.cpp src/stdtree.cpp -o main

debug:
	$(CXX) $(INC) main.cpp -g -o main

unit_tests:
	$(CXX) $(CXXFLAGS) $(INC) src/stdtree.cpp ./test/unit_tests.cpp -lgtest -o unit_tests
	./unit_tests
	rm unit_tests
