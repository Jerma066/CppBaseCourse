#include "geo2d_vector.h"

namespace geometry2D {
bool Segment::IsIntersect(const Segment &seg1, const Segment &seg2) {
  float res1 =
      Vector::VectorProduct(Vector(seg1.p1, seg2.p1), Vector(seg1.p1, seg1.p2));
  float res2 =
      Vector::VectorProduct(Vector(seg1.p1, seg2.p2), Vector(seg1.p1, seg1.p2));
  if (res1 * res2 > 0)
    return false;

  res1 =
      Vector::VectorProduct(Vector(seg2.p2, seg1.p2), Vector(seg2.p2, seg2.p1));
  res2 =
      Vector::VectorProduct(Vector(seg2.p2, seg1.p1), Vector(seg2.p2, seg2.p1));
  if (res1 * res2 > 0)
    return false;

  return true;
}

} // namespace geometry2D
