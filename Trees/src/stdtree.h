#pragma once

#include <cstddef>
#include <set>
#include <utility>

namespace tree {

class Standart {
public:
  Standart() = default;

public:
  void insertKey(int key) { tree.insert(key); }

  size_t getRangeQuerieCount(int first, int second);

private:
  using tree_iter = typename std::set<int>::iterator;
  std::set<int> tree;
};

} // namespace tree
