#include "geo3d_plane.h"

namespace geometry3D {

namespace detail {
std::tuple<float, float> Kramer2D(float kx1, float ky1, float cst1, float kx2,
                                  float ky2, float cst2) {
  Vector equation1 = Vector(Point(kx1, ky1, cst1));
  Vector equation2 = Vector(Point(kx2, ky2, cst2));
  Vector lambda = Vector::VectorProduct(equation1, equation2);
  return std::make_tuple((-1) * lambda.dir.x / lambda.dir.z,
                         (-1) * lambda.dir.y / lambda.dir.z);
}

} // namespace detail

// Static methods
Line Plane::getIntersectionLine(const Plane &pl1, const Plane &pl2) {
  Line result;
  result.dir = Vector::VectorProduct(pl1.normal, pl2.normal);

  if (Vector::ScalarProduct(result.dir, Axis::Z) != 0) {
    result.startPt.z = 0;
    std::tie(result.startPt.x, result.startPt.y) =
        detail::Kramer2D(pl1.normal.dir.x, pl1.normal.dir.y, -pl1.D,
                         pl2.normal.dir.x, pl2.normal.dir.y, -pl2.D);
  } else if (Vector::ScalarProduct(result.dir, Axis::Y) != 0) {
    result.startPt.y = 0;
    std::tie(result.startPt.x, result.startPt.z) =
        detail::Kramer2D(pl1.normal.dir.x, pl1.normal.dir.z, -pl1.D,
                         pl2.normal.dir.x, pl2.normal.dir.z, -pl2.D);
  } else if (Vector::ScalarProduct(result.dir, Axis::X) != 0) {
    result.startPt.x = 0;
    std::tie(result.startPt.y, result.startPt.z) =
        detail::Kramer2D(pl1.normal.dir.y, pl1.normal.dir.z, -pl1.D,
                         pl2.normal.dir.y, pl2.normal.dir.z, -pl2.D);
  }

  return result;
}

} // namespace geometry3D

// Plane operators
bool operator==(const geometry3D::Plane &lhs, const geometry3D::Plane &rhs) {
  return lhs.normal == rhs.normal && lhs.D == rhs.D;
}
