cmake_minimum_required (VERSION 3.10)
project (Trees)

# Set up the build mode - default is Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

# Define the C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Include directories
include_directories(src/)

# Specify executable sources
set(TARGET_SOURCES ./src/stdtree.cpp)

# Define the executable
add_executable(main main.cpp ${TARGET_SOURCES})
add_executable(time_comparison time.cpp ${TARGET_SOURCES})

# Unit tests
enable_testing()
find_package(GTest REQUIRED)

add_executable(unit_tests test/unit_tests.cpp ${TARGET_SOURCES})
target_link_libraries(unit_tests GTest::GTest GTest::Main -lgtest)
add_test(NAME unit_tests COMMAND unit_tests)

