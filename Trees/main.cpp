#include "avltree.hpp"

#include <iostream>
#include <vector>

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
  //std::vector<int> result;
  std::vector<int> fastResult;
  //result.reserve(M + 1);

  for (size_t i = 0; i < M; i++) {
    int from;
    std::cin >> from;
    int to;
    std::cin >> to;
    //    result.push_back(avlTree.getRangeQuerieCount(from, to));
    fastResult.push_back(avlTree.fastGetRangeQuerieCount(from, to));
  }
  /*
    std::cout << "Golden: ";
    for (int val : result)
      std::cout << val << " ";
    std::cout << std::endl;

    std::cout << "Fast: ";
  */
  for (int val : fastResult)
    std::cout << val << " ";
  std::cout << std::endl;
}
