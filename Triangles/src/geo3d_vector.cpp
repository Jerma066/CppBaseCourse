#include "geo3d_triangle.h"

// Triangle methods
namespace geometry3D {

// Static methods
float Vector::ScalarProduct(const Vector &lhs, const Vector &rhs) {
  float prodRes = (lhs.dir.x * rhs.dir.x) + (lhs.dir.y * rhs.dir.y) +
                  (lhs.dir.z * rhs.dir.z);
  return prodRes;
}

Vector Vector::VectorProduct(const Vector &lhs, const Vector &rhs) {
  Vector prodRes;
  prodRes.dir.x = (lhs.dir.y * rhs.dir.z) - (rhs.dir.y * lhs.dir.z);
  prodRes.dir.y = (rhs.dir.x * lhs.dir.z) - (lhs.dir.x * rhs.dir.z);
  prodRes.dir.z = (lhs.dir.x * rhs.dir.y) - (rhs.dir.x * lhs.dir.y);
  return prodRes;
}

} // namespace geometry3D

// Vector operators
bool operator==(const geometry3D::Vector &lhs, const geometry3D::Vector &rhs) {
  return lhs.dir == rhs.dir;
}
