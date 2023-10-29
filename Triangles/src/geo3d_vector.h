#pragma once

#include "geo3d_point.h"

namespace geometry3D {

struct Vector {
  Vector() = default;

  Vector(const Point &from, const Point &to)
      : dir{to.x - from.x, to.y - from.y, to.z - from.z} {}

  static float ScalarProduct(const Vector &lhs, const Vector &rhs);
  static Vector VectorProduct(const Vector &lhs, const Vector &rhs);

  Point dir;
};

} // namespace geometry3D

// Vector operators
bool operator==(const geometry3D::Vector &lhs, const geometry3D::Vector &rhs);
