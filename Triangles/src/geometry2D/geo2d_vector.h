#pragma once

#include "geo2d_point.h"

namespace geometry2D {

struct Vector final {
  Vector(Point from, Point to) : dir(to.x - from.x, to.y - from.y) {}

  static float VectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.dir.x * rhs.dir.y - rhs.dir.x * lhs.dir.y;
  }

  Point dir;
};

struct Segment {
  Segment(Point fp, Point sp) : p1(fp), p2(sp) {}

  static bool IsIntersect(const Segment &seg1, const Segment &seg2);

  Point p1, p2;
};

} // namespace geometry2D
