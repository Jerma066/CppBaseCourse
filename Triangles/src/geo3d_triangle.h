#pragma once

#include <istream>

#include "geo3d_vector.h"

namespace geometry3D {

struct Triangle {

  bool isIntersect(const Triangle& tr) const;

  Point p1, p2, p3;
};

} // namespace geometry3D

// Triangle operators
std::basic_istream<char> &operator>>(std::basic_istream<char> &IS,
                                     geometry3D::Triangle &tl);
bool operator==(const geometry3D::Triangle &lhs,
                const geometry3D::Triangle &rhs);
