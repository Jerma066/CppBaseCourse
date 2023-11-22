#include "geo3d_triangle.h"

// Triangle methods
namespace geometry3D {

Vector Triangle::getNormalVector() const {
  Vector vecP12(p1, p2);
  Vector vecP23(p2, p3);
  Vector normalVec = Vector::VectorProduct(vecP12, vecP23);
  return normalVec.divideByScalar(normalVec.length());
}

Plane Triangle::getPlane() const {
  Vector normal = getNormalVector();
  float D = -1 * Vector::ScalarProduct(normal, Vector(p3));
  return Plane{normal, D};
}

Triangle::IntersectionKind Triangle::isIntersect(const Plane &pl) const {
  float p1Sbst = pl.substitutePoint(p1);
  float p2Sbst = pl.substitutePoint(p2);
  float p3Sbst = pl.substitutePoint(p3);

  if (p1Sbst == 0 && p2Sbst == 0 && p3Sbst == 0) {
    return Triangle::LiesIn;
  } else if (p1Sbst == 0 || p2Sbst == 0 || p3Sbst == 0) {
    if (p1Sbst != 0) {
      return Triangle::P1Intersection;
    } else if (p2Sbst != 0) {
      return Triangle::P2Intersection;
    } else if (p3Sbst != 0) {
      return Triangle::P3Intersection;
    }
  }

  size_t cnt = 0;
  cnt = (p1Sbst > 0) ? cnt + 1 : cnt;
  cnt = (p2Sbst > 0) ? cnt + 1 : cnt;
  cnt = (p3Sbst > 0) ? cnt + 1 : cnt;

  if (cnt == 1) {
    if (p1Sbst > 0) {
      return Triangle::P1Intersection;
    } else if (p2Sbst > 0) {
      return Triangle::P2Intersection;
    } else if (p3Sbst > 0) {
      return Triangle::P3Intersection;
    }
  }

  if (cnt == 2) {
    if (p1Sbst < 0) {
      return Triangle::P1Intersection;
    } else if (p2Sbst < 0) {
      return Triangle::P2Intersection;
    } else if (p3Sbst < 0) {
      return Triangle::P3Intersection;
    }
  }

  return Triangle::NoIntersection;
}

bool Triangle::isIntersect(const Triangle& tr) const {
  // Compute plane equation of triangles
  // Reject as trival if all points of triangles are on same side
  auto trglPlane = tr.getPlane();
  Triangle::IntersectionKind IntersectP2T1 = isIntersect(trglPlane);
  if (IntersectP2T1 == Triangle::NoIntersection)
    return false;

  auto thisPlane = getPlane();
  Triangle::IntersectionKind IntersectP1T2 = tr.isIntersect(thisPlane);
  if (IntersectP1T2 == Triangle::NoIntersection)
    return false;

  bool isCoplanar = (IntersectP1T2 == Triangle::LiesIn) &&
                    (IntersectP2T1 == Triangle::LiesIn);
  if (!isCoplanar) {
    return false;
  }

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
