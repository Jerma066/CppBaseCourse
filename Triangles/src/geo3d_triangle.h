#pragma once

#include <cassert>
#include <istream>

#include "geo3d_plane.h"
#include "geo3d_vector.h"
#include "geometry2D/geo2d_triangle.h"

// Triangle methods
namespace geometry3D {

struct Triangle final {
  Triangle() = default;
  Triangle(Point pt1, Point pt2, Point pt3) : p1(pt1), p2(pt2), p3(pt3) {}

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

private:
  std::pair<float, float>
  findProjectionOnIntersectionLine(const Line &intersectionLine,
                                   const Plane &trPlane,
                                   IntersectionKind interPosition) const;

  geometry2D::Triangle
      getAxisAlignedProjection(Plane::AxisAlignedPlaneKind) const;

public:
  Point p1, p2, p3;
  const float epsilon = std::pow(10.0, -14.0);
};

} // namespace geometry3D

// Triangle operators
std::basic_istream<char> &operator>>(std::basic_istream<char> &IS,
                                     geometry3D::Triangle &tl);
bool operator==(const geometry3D::Triangle &lhs,
                const geometry3D::Triangle &rhs);
