#include "geo3d_point.h"

// Point operators
std::basic_istream<char> &operator>>(std::basic_istream<char> &IS,
                                     geometry3D::Point &pt) {
  IS >> pt.x >> pt.y >> pt.z;
  return IS;
}

bool operator==(const geometry3D::Point &lhs, const geometry3D::Point &rhs) {
  return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}
