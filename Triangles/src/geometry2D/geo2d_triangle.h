#pragma once

#include "geo2d_vector.h"

namespace geometry2D {

struct Triangle final {
  Triangle() = default;
  Triangle(const Triangle &tr) : p1(tr.p1), p2(tr.p2), p3(tr.p3) {}
  Triangle(const Point &p1, const Point &p2, const Point &p3)
      : p1(p1), p2(p2), p3(p3) {}

  bool isPointLiesIn(const Point &pt) const;
  bool isIntersect(const Triangle &tr) const;

  Point p1, p2, p3;
};

} // namespace geometry2D
