#pragma once

#include <cstddef>
#include <set>
#include <utility>

namespace tree {

class Standard {
public:
  Standard() = default;

public:
  void insert(int key) { tree.insert(key); }

  size_t getRangeQuerieCount(int first, int second);

private:
  using tree_iter = typename std::set<int>::iterator;
  std::set<int> tree;
};

} // namespace tree
