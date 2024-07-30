#include <gtest/gtest.h>

#include "avltree.hpp"
#include "stdtree.h"

TEST(StdTree, Correctness) {
  tree::Standard stdTree;
  stdTree.insertKey(10);
  stdTree.insertKey(20);
  stdTree.insertKey(30);
  stdTree.insertKey(40);
  stdTree.insertKey(50);

  EXPECT_EQ(stdTree.getRangeQuerieCount(29, 41), 2);
  EXPECT_EQ(stdTree.getRangeQuerieCount(40, 50), 2);
  EXPECT_EQ(stdTree.getRangeQuerieCount(39, 50), 2);
  EXPECT_EQ(stdTree.getRangeQuerieCount(41, 50), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(41, 51), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(39, 51), 2);
  EXPECT_EQ(stdTree.getRangeQuerieCount(40, 41), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(50, 51), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(10, 20), 2);
  EXPECT_EQ(stdTree.getRangeQuerieCount(20, 30), 2);
  EXPECT_EQ(stdTree.getRangeQuerieCount(29, 31), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(49, 51), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(9, 11), 1);

  EXPECT_EQ(stdTree.getRangeQuerieCount(10, 10), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(20, 20), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(30, 30), 1);
  EXPECT_EQ(stdTree.getRangeQuerieCount(40, 40), 1);

  EXPECT_EQ(stdTree.getRangeQuerieCount(7, 7), 0);
  EXPECT_EQ(stdTree.getRangeQuerieCount(31, 31), 0);
  EXPECT_EQ(stdTree.getRangeQuerieCount(101, 101), 0);
  EXPECT_EQ(stdTree.getRangeQuerieCount(30, 10), 3);
}

TEST(AVLTree, Insert) {
  {
    tree::AVL<int> avlTree;
    avlTree.insert(0);
    avlTree.insert(1);
    avlTree.insert(1);

    auto values = avlTree.getBfsTravers();
    EXPECT_EQ(values.size(), 2);
    EXPECT_EQ(values[0], 0);
    EXPECT_EQ(values[1], 1);
  }
}

TEST(AVLTree, Rebalance) {
  {
    tree::AVL<int> avlTree;
    avlTree.insert(5);
    avlTree.insert(4);
    avlTree.insert(3);
    auto values = avlTree.getBfsTravers();

    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values[0], 4);
    EXPECT_EQ(values[1], 3);
    EXPECT_EQ(values[2], 5);
    EXPECT_EQ(avlTree.isBalanced(), true);
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(3);
    avlTree.insert(4);
    avlTree.insert(5);
    auto values = avlTree.getBfsTravers();

    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values[0], 4);
    EXPECT_EQ(values[1], 3);
    EXPECT_EQ(values[2], 5);
    EXPECT_EQ(avlTree.isBalanced(), true);
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(5);
    avlTree.insert(4);
    avlTree.insert(3);
    avlTree.insert(2);
    auto values = avlTree.getBfsTravers();

    EXPECT_EQ(values.size(), 4);
    EXPECT_EQ(values[0], 4);
    EXPECT_EQ(values[1], 3);
    EXPECT_EQ(values[2], 5);
    EXPECT_EQ(values[3], 2);
    EXPECT_EQ(avlTree.isBalanced(), true);

    avlTree.insert(5);
    avlTree.insert(3);

    EXPECT_EQ(values.size(), 4);
    EXPECT_EQ(values[0], 4);
    EXPECT_EQ(values[1], 3);
    EXPECT_EQ(values[2], 5);
    EXPECT_EQ(values[3], 2);
    EXPECT_EQ(avlTree.isBalanced(), true);
  }

  {
    std::vector<int> randomValues = {
        35, 48, 83, 61, 1,  69, 45, 20, 31, 68, 41, 56, 75, 22, 34, 74, 72, 27,
        79, 63, 44, 9,  40, 26, 12, 42, 81, 88, 10, 87, 84, 52, 67, 73, 46, 76,
        24, 53, 14, 8,  78, 80, 55, 4,  38, 3,  28, 62, 32, 47, 29, 51, 11, 30,
        71, 15, 37, 59, 60, 70, 49, 5,  36, 17, 39, 43, 13, 18, 66, 58, 77, 54,
        89, 6,  19, 65, 57, 50, 86, 23, 16, 7,  2,  33, 25, 90, 82, 21, 85, 64};

    tree::AVL<int> avlTree;
    for (auto val : randomValues)
      avlTree.insert(val);

    EXPECT_EQ(avlTree.isBalanced(), true);
  }

  {
    std::vector<int> randomValues = {13, 20, 18, 24, 11, 1,  8, 3, 17,
                                     19, 10, 14, 5,  12, 25, 4, 6, 9,
                                     7,  21, 23, 15, 22, 16, 2};
    tree::AVL<int> avlTree;
    for (auto val : randomValues) {
      avlTree.insert(val);
      EXPECT_EQ(avlTree.isBalanced(), true);
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
