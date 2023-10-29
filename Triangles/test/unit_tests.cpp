#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "geo3d_triangle.h"

// ----- LFU tests ------------------------------------------------------------
TEST(Geometry3D, PointCinCheck) {
  std::string buf = "1 2 3";
  std::stringstream IOS(buf);

  geometry3D::Point pt;
  IOS >> pt;

  geometry3D::Point expected{1, 2, 3};
  bool res = (pt == expected);
  EXPECT_EQ(res, true);
}

TEST(Geometry3D, TriangleCinCheck) {
  std::string buf = "1 2 3 4 5 6 7 8 9";
  std::stringstream IOS(buf);

  geometry3D::Triangle tl;
  IOS >> tl;

  geometry3D::Triangle expected{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  bool res = (tl == expected);
  EXPECT_EQ(res, true);
}

TEST(Geometry3D, ScalarProduct) {
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

TEST(Geometry3D, VectorProduct) {
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
