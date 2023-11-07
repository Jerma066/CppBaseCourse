#include "geo3d_triangle.h"

// Triangle methods
namespace geometry3D {

Vector Triangle::getNormalVector() const {
  Vector vecP12(p1, p2);
  Vector vecP23(p2, p3);
  Vector normalVec = Vector::VectorProduct(vecP12, vecP23);
  return normalVec.divideByScalar(normalVec.length());
}

bool Triangle::isIntersect(const Triangle& tr) const {
  // 1. Compute the normal vectors for each triangle.

  return false;
}

} // geometry3D

// Triangle operators
std::basic_istream<char> &operator>>(std::basic_istream<char> &IS,
                                     geometry3D::Triangle &tl) {
  IS >> tl.p1 >> tl.p2 >> tl.p3;
  return IS;
}

bool operator==(const geometry3D::Triangle &lhs,
                const geometry3D::Triangle &rhs) {
  return (lhs.p1 == rhs.p1) && (lhs.p2 == rhs.p2) && (lhs.p3 == rhs.p3);
}
