CXX=g++
CXXFLAGS= -std=c++1z

all:
	$(CXX) $(CXXFLAGS) main.cpp -o main

unit_tests:
	$(CXX) $(CXXFLAGS) unit_tests.cpp -lgtest -o unit_tests
	./unit_tests
	mrm unit_tests


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
