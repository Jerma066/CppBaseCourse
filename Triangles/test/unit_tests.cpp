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
  geometry3D::Point p1({0, 0, 0});
  geometry3D::Point p2({3, 0, 0});
  geometry3D::Point p3({0, 4, 0});
  geometry3D::Triangle pifTr({p1, p2, p3});

  geometry3D::Vector expectedNorm({0, 0, 1});
  bool res = (pifTr.getNormalVector() == expectedNorm);
  EXPECT_EQ(res, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
