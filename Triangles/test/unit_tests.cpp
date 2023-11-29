#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "geo3d_triangle.h"

TEST(Geometry3DPoint, CinCheck) {
  std::string buf = "1 2 3";
  std::stringstream IOS(buf);

  geometry3D::Point pt;
  IOS >> pt;

  geometry3D::Point expected{1, 2, 3};
  bool res = (pt == expected);
  EXPECT_EQ(res, true);
}

TEST(Geometry3DTriangle, CinCheck) {
  std::string buf = "1 2 3 4 5 6 7 8 9";
  std::stringstream IOS(buf);

  geometry3D::Triangle tl;
  IOS >> tl;

  geometry3D::Triangle expected{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  bool res = (tl == expected);
  EXPECT_EQ(res, true);
}

TEST(Geometry3DVector, ScalarProduct) {
  geometry3D::Point from{0, 0, 0};

  geometry3D::Vector xAxis(from, {1, 0, 0});
  geometry3D::Vector yAxis(from, {0, 1, 0});
  geometry3D::Vector zAxis(from, {0, 0, 1});

  float expected = 0;
  float res = geometry3D::Vector::ScalarProduct(xAxis, yAxis);
  EXPECT_EQ(res, expected);

  res = geometry3D::Vector::ScalarProduct(yAxis, zAxis);
  EXPECT_EQ(res, expected);

  res = geometry3D::Vector::ScalarProduct(zAxis, xAxis);
  EXPECT_EQ(res, expected);
}

TEST(Geometry3DVector, VectorProduct) {
  geometry3D::Point from{0, 0, 0};

  geometry3D::Vector xAxis(from, {1, 0, 0});
  geometry3D::Vector yAxis(from, {0, 1, 0});
  geometry3D::Vector zAxis(from, {0, 0, 1});

  bool res = geometry3D::Vector::VectorProduct(xAxis, yAxis) == zAxis;
  EXPECT_EQ(res, true);

  res = geometry3D::Vector::VectorProduct(yAxis, zAxis) == xAxis;
  EXPECT_EQ(res, true);

  res = geometry3D::Vector::VectorProduct(zAxis, xAxis) == yAxis;
  EXPECT_EQ(res, true);
}

TEST(Geometry3DVector, Length) {
  float expected = 6;
  {
    geometry3D::Vector vec({4, 4, 2});
    EXPECT_EQ(vec.length(), expected);
  }

  expected = 11;
  {
    geometry3D::Vector vec({9, 2, 6});
    EXPECT_EQ(vec.length(), expected);
  }

  expected = 12;
  {
    geometry3D::Vector vec({4, 8, 8});
    EXPECT_EQ(vec.length(), expected);
  }
}

TEST(Geometry3DVector, DivideByScalar) {
  {
    geometry3D::Vector vec({4, 2, 4});
    vec.divideByScalar(2);
    EXPECT_EQ(vec.dir.x, 2);
    EXPECT_EQ(vec.dir.y, 1);
    EXPECT_EQ(vec.dir.z, 2);
  }

  {
    geometry3D::Vector vec({6, 9, 2});
    vec.divideByScalar(11);
    EXPECT_EQ(vec.length(), 1);
  }
}

TEST(Geometry3DTriangle, GetNormalVector) {
  geometry3D::Point p1(0, 0, 0);
  geometry3D::Point p2(3, 0, 0);
  geometry3D::Point p3(0, 4, 0);
  geometry3D::Triangle pifTr({p1, p2, p3});

  geometry3D::Vector expectedNorm({0, 0, 1});
  bool res = (pifTr.getNormalVector() == expectedNorm);
  EXPECT_EQ(res, true);
}

TEST(Geometry3DMisc, Kramer2D) {
  {
    bool res =
        geometry3D::detail::Kramer2D(1, 0, 3, 0, 2, 8) == std::make_tuple(3, 4);
    EXPECT_EQ(res, true);
  }

  {
    bool res = geometry3D::detail::Kramer2D(1, 6, 4, 7, 2, 8) ==
               std::make_tuple(1, 0.5);
    EXPECT_EQ(res, true);
  }
}

TEST(Geometry3DPlane, getIntersectionLine) {
  using namespace geometry3D;

  {
    Plane fplane(2, 3, 0, 1);
    Plane splane(1, -2, 1, -3);
    Line res = Plane::getIntersectionLine(fplane, splane);
    bool dirRes = (res.dir == Vector({3, -2, -7}));
    bool startPtRes = (res.startPt == Point(1, -1, 0));
    EXPECT_EQ(dirRes, true);
    EXPECT_EQ(startPtRes, true);
  }

  {
    Plane fplane(1, 0, 3, 7);
    Plane splane(2, 3, 3, 2);
    Line res = Plane::getIntersectionLine(fplane, splane);
    EXPECT_EQ(res.dir == Vector({-9, 3, 3}), true);
    EXPECT_EQ(res.startPt == Point(-7, 4, 0), true);
  }

  {
    Plane fplane(1, 2, -3, -2);
    Plane splane(1, 0, -1, 4);
    Line res = Plane::getIntersectionLine(fplane, splane);
    EXPECT_EQ(res.dir == Vector({-2, -2, -2}), true);
    EXPECT_EQ(res.startPt == Point(-4, 3, 0), true);
  }

  {
    Plane fplane(2, 1, -1, -1);
    Plane splane(1, 3, -2, 0);
    Line res = Plane::getIntersectionLine(fplane, splane);
    EXPECT_EQ(res.dir == Vector({1, 3, 5}), true);
    EXPECT_EQ(res.startPt == Point(0.6, -0.2, 0), true);
  }

  {
    Plane fplane(0, 1, 0, 0);
    Plane splane(0, 0, 1, 0);
    Line res = Plane::getIntersectionLine(fplane, splane);
    EXPECT_EQ(res.dir == Vector({1, 0, 0}), true);
    EXPECT_EQ(res.startPt == Point(0, 0, 0), true);
  }

  {
    Plane fplane(0, 0, 1, 0);
    Plane splane(1, 0, 0, 0);
    Line res = Plane::getIntersectionLine(fplane, splane);
    EXPECT_EQ(res.dir == Vector({0, 1, 0}), true);
    EXPECT_EQ(res.startPt == Point(0, 0, 0), true);
  }

  {
    Plane fplane(1, 0, 0, 0);
    Plane splane(0, 1, 0, 0);
    Line res = Plane::getIntersectionLine(fplane, splane);
    EXPECT_EQ(res.dir == Vector({0, 0, 1}), true);
    EXPECT_EQ(res.startPt == Point(0, 0, 0), true);
  }
}

TEST(Geometry3DTriangle, GetPlane) {
  {
    geometry3D::Point p1(0, 0, 0);
    geometry3D::Point p2(3, 0, 0);
    geometry3D::Point p3(0, 4, 0);
    geometry3D::Triangle pifTr({p1, p2, p3});

    geometry3D::Plane expectedPlane(0, 0, 1, 0);
    EXPECT_EQ(pifTr.getPlane() == expectedPlane, true);
  }

  {
    geometry3D::Point p1(0, 4, 7);
    geometry3D::Point p2(3, 0, 7);
    geometry3D::Point p3(0, 0, 7);
    geometry3D::Triangle pifTr({p1, p2, p3});

    geometry3D::Plane expectedPlane(0, 0, -1, 7);
    EXPECT_EQ(pifTr.getPlane() == expectedPlane, true);
  }
  {
    geometry3D::Point p1(0, 4, 7);
    geometry3D::Point p2(3, 0, 7);
    geometry3D::Point p3(0, 0, 7);
    geometry3D::Triangle pifTr({p1, p2, p3});

    geometry3D::Plane expectedPlane(0, 0, -1, 7);
    EXPECT_EQ(pifTr.getPlane() == expectedPlane, true);
  }
}

TEST(Geometry3DTriangle, IsIntersectPlane) {
  using namespace geometry3D;
  {
    geometry3D::Point p1(0, 0, 0);
    geometry3D::Point p2(3, 0, 0);
    geometry3D::Point p3(0, 4, 0);
    geometry3D::Triangle tr({p1, p2, p3});

    geometry3D::Plane xy1(0, 0, 1, 1);
    EXPECT_EQ(tr.isIntersect(xy1) == Triangle::NoIntersection, true);
  }

  {
    geometry3D::Point p1(5, 0, 2);
    geometry3D::Point p2(0, 3, 2);
    geometry3D::Point p3(0, -3, 2);
    geometry3D::Triangle tr({p1, p2, p3});

    geometry3D::Plane yz4(1, 0, 0, -4);
    EXPECT_EQ(tr.isIntersect(yz4) == Triangle::P1Intersection, true);
  }
}

TEST(Geometry3DTriangle, NonCoplanarIntersection) {
  using namespace geometry3D;
  {
    Triangle tr1(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));
    Triangle tr2(Point(0, 0, 0.01), Point(5, 5, 0.01), Point(5, 5, -0.09));
    EXPECT_EQ(tr1.isIntersect(tr2), true);
    EXPECT_EQ(tr2.isIntersect(tr1), true);
  }
  {
    Triangle tr1(Point(5, 0, 2), Point(0, 3, 2), Point(0, -3, 2));
    Triangle tr2(Point(0, 0, 7), Point(0, 2.57, -2), Point(0, -2.57, -2));
    EXPECT_EQ(tr1.isIntersect(tr2), true);
    EXPECT_EQ(tr2.isIntersect(tr1), true);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
