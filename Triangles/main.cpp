#include "geo3d_triangle.h"

#include <iostream>
#include <set>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<geometry3D::Triangle> trianglesVector;
  std::set<int> result;

  for (int i = 0; i < n; i++) {
    geometry3D::Triangle tr;
    std::cin >> tr;
    trianglesVector.push_back(tr);
  }

  for (int i = 0; i < n; i++) {
    if (result.find(i) != result.end())
      continue;

    for (int j = 0; j < n; j++) {
      if ((i != j) && trianglesVector[i].isIntersect(trianglesVector[j])) {
        result.insert(i);
        result.insert(j);
        break;
      }
    }
  }

  for (auto elem : result)
    std::cout << elem << "\n";

  return 0;
}
