#pragma once

#include <istream>

#include "geo3d_plane.h"
#include "geo3d_vector.h"

// Triangle methods
namespace geometry3D {

struct Triangle final {
  enum IntersectionKind {
    NoIntersection,
    P1Intersection,
    P2Intersection,
    P3Intersection,
    LiesIn
  };

  Vector getNormalVector() const;
  Plane getPlane() const;

  IntersectionKind isIntersect(const Plane &pl) const;
  bool isIntersect(const Triangle& tr) const;

  Point p1, p2, p3;
  const float epsilon = std::pow(10.0, -14.0);
};

} // namespace geometry3D

// Triangle operators
std::basic_istream<char> &operator>>(std::basic_istream<char> &IS,
                                     geometry3D::Triangle &tl);
bool operator==(const geometry3D::Triangle &lhs,
                const geometry3D::Triangle &rhs);
