#pragma once

#include <tuple>
#include <utility>

#include "geo3d_vector.h"

namespace geometry3D {

namespace detail {

std::tuple<float, float> Kramer2D(float kx1, float ky1, float cst1, float kx2,
                                  float ky2, float cst2);

} // namespace detail

struct Line {
  Vector dir;
  Point startPt;
};

struct Plane final {
  Plane(float kx, float ky, float kz, float d) : normal({kx, ky, kz}), D(d) {}
  Plane(Vector norm, float d) : normal(norm), D(d) {}

  enum AxisAlignedPlaneKind { XY, YZ, XZ };

  float substitutePoint(const Point &pt) const {
    return D + Vector::ScalarProduct(normal, Vector(pt));
  }

  static Line getIntersectionLine(const Plane &pl1, const Plane &pl2);

  Vector normal;
  float D;
};

} // namespace geometry3D

// Plane operators
bool operator==(const geometry3D::Plane &lhs, const geometry3D::Plane &rhs);
