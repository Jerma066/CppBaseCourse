#include "geo2d_triangle.h"

namespace geometry2D {

bool Triangle::isPointLiesIn(const Point &pt) const {
  float z1 = Vector::VectorProduct(Vector(p1, p2), Vector(p1, pt));
  float z2 = Vector::VectorProduct(Vector(p2, p3), Vector(p2, pt));
  float z3 = Vector::VectorProduct(Vector(p3, p1), Vector(p3, pt));

  // Lies on the edge of the triangle;
  if (z1 * z2 * z3 == 0) {
    float z12 = z1 * z2;
    float z23 = z2 * z3;
    float z13 = z1 * z3;
    if (z12 > 0 || z23 > 0 || z13 > 0) {
      return true;
    } else if (z12 < 0 || z23 < 0 || z13 < 0) {
      return false;
    }
  }

  // Lies inside the triangle
  int signs = ((z1 > 0) ? 1 : 0) + ((z2 > 0) ? 1 : 0) + ((z3 > 0) ? 1 : 0);
  if (signs == 0 || signs == 3)
    return true;

  return false;
}

bool Triangle::isIntersect(const Triangle &tr) const {
  // 1. Edge intersection test
  bool isEdgeIntersection =
      Segment::IsIntersect(Segment(p1, p2), Segment(tr.p1, tr.p2)) ||
      Segment::IsIntersect(Segment(p1, p2), Segment(tr.p1, tr.p3)) ||
      Segment::IsIntersect(Segment(p1, p2), Segment(tr.p2, tr.p3)) ||

      Segment::IsIntersect(Segment(p1, p3), Segment(tr.p1, tr.p2)) ||
      Segment::IsIntersect(Segment(p1, p3), Segment(tr.p1, tr.p3)) ||
      Segment::IsIntersect(Segment(p1, p3), Segment(tr.p2, tr.p3)) ||

      Segment::IsIntersect(Segment(p2, p3), Segment(tr.p1, tr.p2)) ||
      Segment::IsIntersect(Segment(p2, p3), Segment(tr.p1, tr.p3)) ||
      Segment::IsIntersect(Segment(p2, p3), Segment(tr.p2, tr.p3));

  if (isEdgeIntersection)
    return true;

  // 2. Point-in-triangle test
  bool isVertexInTriangle = isPointLiesIn(tr.p1) || isPointLiesIn(tr.p2) ||
                            isPointLiesIn(tr.p3) || tr.isPointLiesIn(p3) ||
                            tr.isPointLiesIn(p1) || tr.isPointLiesIn(p3);

  return isVertexInTriangle;
}

} // namespace geometry2D
