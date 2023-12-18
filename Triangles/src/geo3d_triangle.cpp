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

std::pair<float, float> Triangle::findProjectionOnIntersectionLine(
    const Line &intersectLine, const Plane &trPlane,
    IntersectionKind interPosition) const {

  float pv1 = Vector::ScalarProduct(intersectLine.dir,
                                    Vector(intersectLine.startPt, p1));
  float pv2 = Vector::ScalarProduct(intersectLine.dir,
                                    Vector(intersectLine.startPt, p2));
  float pv3 = Vector::ScalarProduct(intersectLine.dir,
                                    Vector(intersectLine.startPt, p3));

  auto calcIntersectionIntervalValues = [](float pv1, float pv2, float d1,
                                           float d2) {
    if (d2 == 0 || d2 == -0)
      return pv2;

    return pv2 + ((pv1 - pv2) * d2 / (d2 - d1));
  };

  float t1 = 0, t2 = 0;
  switch (interPosition) {
  case Triangle::P1Intersection: {
    t1 = calcIntersectionIntervalValues(pv1, pv2, trPlane.substitutePoint(p1),
                                        trPlane.substitutePoint(p2));
    t2 = calcIntersectionIntervalValues(pv1, pv3, trPlane.substitutePoint(p1),
                                        trPlane.substitutePoint(p3));
    break;
  }
  case Triangle::P2Intersection: {
    t1 = calcIntersectionIntervalValues(pv2, pv1, trPlane.substitutePoint(p2),
                                        trPlane.substitutePoint(p1));
    t2 = calcIntersectionIntervalValues(pv2, pv3, trPlane.substitutePoint(p2),
                                        trPlane.substitutePoint(p3));
    break;
  }
  case Triangle::P3Intersection: {
    t1 = calcIntersectionIntervalValues(pv3, pv1, trPlane.substitutePoint(p3),
                                        trPlane.substitutePoint(p1));
    t2 = calcIntersectionIntervalValues(pv3, pv2, trPlane.substitutePoint(p3),
                                        trPlane.substitutePoint(p2));
    break;
  }
  default:
    // TODO: provide some error report
    break;
  }

  return std::make_pair(std::min(t1, t2), std::max(t1, t2));
}

geometry2D::Triangle Triangle::getAxisAlignedProjection(
    Plane::AxisAlignedPlaneKind planeKind) const {
  geometry2D::Triangle Res;

  switch (planeKind) {
  case Plane::XY:
    Res.p1 = geometry2D::Point(p1.x, p1.y);
    Res.p2 = geometry2D::Point(p2.x, p2.y);
    Res.p3 = geometry2D::Point(p3.x, p3.y);
    break;
  case Plane::YZ:
    Res.p1 = geometry2D::Point(p1.y, p1.z);
    Res.p2 = geometry2D::Point(p2.y, p2.z);
    Res.p3 = geometry2D::Point(p3.y, p3.z);
    break;
  case Plane::XZ:
    Res.p1 = geometry2D::Point(p1.x, p1.z);
    Res.p2 = geometry2D::Point(p2.x, p2.z);
    Res.p3 = geometry2D::Point(p3.x, p3.z);
    break;
  }

  return Res;
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
  // Non-coplanar case
  if (!isCoplanar) {
    Line intersectLine = Plane::getIntersectionLine(trglPlane, thisPlane);
    auto thisInterval = findProjectionOnIntersectionLine(
        intersectLine, trglPlane, IntersectP2T1);
    auto trglInterval = tr.findProjectionOnIntersectionLine(
        intersectLine, thisPlane, IntersectP1T2);

    // No intersection between projections
    if ((thisInterval.first > trglInterval.second &&
         thisInterval.second > trglInterval.second) ||
        (trglInterval.first > thisInterval.second &&
         trglInterval.second > thisInterval.second))
      return false;

    return true;
  }

  // Coplanar case
  // TODO: Provide some error report instead of assert
  /*
  assert((thisPlane.normal == trglPlane.normal ||
          thisPlane.normal == trglPlane.normal.divideByScalar(-1)) &&
         "Coplanar triangles should have parralel normal vectors");
  */
  // Projecting triangle onto the axis aligned plane with maximized area
  Plane::AxisAlignedPlaneKind maximizedAreaPlaneKind = Plane::XY;
  auto absNormX = std::abs(thisPlane.normal.dir.x);
  auto absNormY = std::abs(thisPlane.normal.dir.y);
  auto absNormZ = std::abs(thisPlane.normal.dir.z);
  if (absNormX > absNormY && absNormX > absNormZ) {
    maximizedAreaPlaneKind = Plane::YZ;
  } else if (absNormY > absNormZ) {
    maximizedAreaPlaneKind = Plane::XZ;
  }

  geometry2D::Triangle thisProjection =
      getAxisAlignedProjection(maximizedAreaPlaneKind);
  geometry2D::Triangle trglProjection =
      tr.getAxisAlignedProjection(maximizedAreaPlaneKind);

  return thisProjection.isIntersect(trglProjection);
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
