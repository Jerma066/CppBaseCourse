#pragma once

#include <cassert>
#include <iostream>

#include "geo2d_triangle.h"
#include "geo3d_plane.h"
#include "geo3d_vector.h"

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
  bool isIntersect(const Triangle &tr) const;

  void dump(std::basic_ostream<char> &OS = std::cout) {
    OS << "Triagnle: "
       << "{p1(" << p1.x << "," << p1.y << "," << p1.z << "),  "
       << "{p2(" << p2.x << "," << p2.y << "," << p2.z << "),  "
       << "{p3(" << p3.x << "," << p3.y << "," << p3.z << ")}" << std::endl;
  }

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
