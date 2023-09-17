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

CXX=g++
CXXFLAGS= -std=c++1z

unit_tests:
	$(CXX) $(CXXFLAGS) unit_tests.cpp -lgtest -o unit_tests
	./unit_tests
	rm unit_tests
