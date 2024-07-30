#include "stdtree.h"

size_t tree::Standard::getRangeQuerieCount(int first, int second) {
  if (first > second)
    std::swap(first, second);

  tree_iter fi = tree.lower_bound(first);
  tree_iter si = tree.upper_bound(second);

  return std::distance(fi, si);
}
