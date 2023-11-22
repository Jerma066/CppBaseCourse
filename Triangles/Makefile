CXX=g++
CXXFLAGS= -std=c++1z -O2
INC= -I ./src
TARGETS= ./src/geo3d_point.cpp ./src/geo3d_vector.cpp ./src/geo3d_plane.cpp ./src/geo3d_triangle.cpp

all:
	$(CXX) $(CXXFLAGS) $(INC) main.cpp -o main

debug:
	$(CXX) $(INC) main.cpp -g -o main

unit_tests:
	$(CXX) $(CXXFLAGS) $(INC) $(TARGETS) ./test/unit_tests.cpp -lgtest -o unit_tests
	./unit_tests
	rm unit_tests


# --- Should be used with sudo ------------------------------------------------
install_gtest:
	mkdir ../googletest/build
	cmake -B../googletest/build -S../googletest -DBUILD_GMOCK=OFF
	make -C ../googletest/build -j 4
	make install -C ../googletest/build

uninstall_gtest:
	make clean -C ../googletest/build
	rm -rf ../googletest/build
# -----------------------------------------------------------------------------
