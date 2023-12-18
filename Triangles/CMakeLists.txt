cmake_minimum_required (VERSION 3.10)
project (Geometry3D)

# Set up the build mode - default is Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

# Define the C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Include directories
include_directories(src/geometry3D src/geometry2D)

# Specify executable sources
set(TARGET_SOURCES src/geometry3D/geo3d_point.cpp src/geometry3D/geo3d_vector.cpp src/geometry3D/geo3d_plane.cpp src/geometry3D/geo3d_triangle.cpp src/geometry2D/geo2d_triangle.cpp src/geometry2D/geo2d_vector.cpp)

# Define the executable
add_executable(main main.cpp ${TARGET_SOURCES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(main PRIVATE -g)
endif()

# Unit tests
enable_testing()
find_package(GTest REQUIRED)

add_executable(unit_tests test/unit_tests.cpp ${TARGET_SOURCES})
target_link_libraries(unit_tests GTest::GTest GTest::Main -lgtest)
add_test(NAME unit_tests COMMAND unit_tests)
