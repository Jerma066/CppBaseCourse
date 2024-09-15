#include "avltree.hpp"
#include "stdtree.h"

#include <iostream>
#include <vector>
#include <utility>
#include <chrono>

int main() {
  size_t N;
  std::cin >> N;
  tree::AVL<int> avlTree;
  tree::Standard stdTree;
  for (size_t i = 0; i < N; i++) {
    int key;
    std::cin >> key;
    avlTree.insert(key);
    stdTree.insert(key);
  }

  size_t M;
  std::cin >> M;
  std::vector<std::pair<int, int>> ranges;
  ranges.reserve(M);
  for (size_t i = 0; i < M; i++) {
    int from; std::cin >> from;
    int to; std::cin >> to;
    ranges.push_back(std::make_pair(from, to));
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    for (auto range : ranges)
      stdTree.getRangeQuerieCount(range.first, range.second);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "[STD] Execution time: " << duration.count() << " microseconds." << std::endl;
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    for (auto range : ranges)
      avlTree.fastGetRangeQuerieCount(range.first, range.second);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "[AVL] Fast execution time: " << duration.count() << " microseconds." << std::endl;
  }
}
