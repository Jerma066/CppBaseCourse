#include "geo3d_vector.h"

// Vector methods
namespace geometry3D {

// Public methods
float Vector::length() const {
  float lgth = std::sqrt((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));
  return lgth;
}

Vector &Vector::divideByScalar(float scalar) {
  dir.x /= scalar;
  dir.y /= scalar;
  dir.z /= scalar;
  return *this;
}

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
