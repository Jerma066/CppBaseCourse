#pragma once

#include <istream>
#include <ostream>

namespace geometry3D {

struct Point {
  Point() {}
  Point(float x, float y, float z) : x(x), y(y), z(z) {}

  float x, y, z;
};

} // namespace geometry3D

// Point operators
std::basic_istream<char> &operator>>(std::basic_istream<char> &IS,
                                     geometry3D::Point &pt);
bool operator==(const geometry3D::Point &lhs, const geometry3D::Point &rhs);
