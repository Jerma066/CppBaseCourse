#include "avltree.hpp"

#include <iostream>

int main() {
  size_t N;
  std::cin >> N;
  tree::AVL<int> avlTree;
  for (size_t i = 0; i < N; i++) {
    int key;
    std::cin >> key;
    avlTree.insert(key);
  }

  size_t M;
  std::cin >> M;
  for (size_t i = 0; i < M; i++) {
    int from;
    std::cin >> from;
    int to;
    std::cin >> to;
    std::cout << avlTree.fastGetRangeQuerieCount(from, to) << " ";
  }

  std::cout << std::endl;
}
