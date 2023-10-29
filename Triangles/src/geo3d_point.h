#pragma once

#include <istream>

namespace geometry3D {

struct Point {
  float x, y, z;
};

} // namespace geometry3D

// Point operators
std::basic_istream<char> &operator>>(std::basic_istream<char> &IS,
                                     geometry3D::Point &pt);
bool operator==(const geometry3D::Point &lhs, const geometry3D::Point &rhs);
