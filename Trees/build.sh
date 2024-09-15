#!/bin/bash

mkdir -p build
cd build
cmake .. #-DCMAKE_BUILD_TYPE="Debug"
make unit_tests
./unit_tests
rm unit_tests
make main
make time_comparison
