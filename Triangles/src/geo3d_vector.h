#pragma once

#include <cmath>

#include "geo3d_point.h"

namespace geometry3D {

struct Vector final {
  Vector() = default;

  Vector(const Point &direction) : dir(direction) {}

  Vector(const Point &from, const Point &to)
      : dir{to.x - from.x, to.y - from.y, to.z - from.z} {}

  float length() const;
  Vector &divideByScalar(float scalar);

  static float ScalarProduct(const Vector &lhs, const Vector &rhs);
  static Vector VectorProduct(const Vector &lhs, const Vector &rhs);

  Point dir;
};

} // namespace geometry3D

// Vector operators
bool operator==(const geometry3D::Vector &lhs, const geometry3D::Vector &rhs);
