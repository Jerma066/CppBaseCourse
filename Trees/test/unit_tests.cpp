#include <gtest/gtest.h>

#include <cstdlib> // for rand()/srand() functions
#include <ctime>   // for time() function

#include "avltree.hpp"
#include "stdtree.h"

TEST(StdTree, Correctness) {
  tree::Standard stdTree;
  stdTree.insert(10);
  stdTree.insert(20);
  stdTree.insert(30);
  stdTree.insert(40);
  stdTree.insert(50);

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

TEST(AVLTree, Iterators) {
  // operator++ and opearotor--
  {
    tree::AVL<int> avlTree;
    int border = 13824;
    int N = 100;
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < N; i++)
      avlTree.insert(1 + rand() % border);

    std::vector<int> sortedElements;
    sortedElements.reserve(N);
    auto lastElemIter = avlTree.begin();

    // Testing operator++
    auto iter = avlTree.begin();
    auto prevVal = iter->value;
    ++iter;
    for (; iter != avlTree.end(); ++iter) {
      EXPECT_EQ(iter->value > prevVal, true);
      sortedElements.push_back(prevVal);
      prevVal = iter->value;
      lastElemIter = iter;
    }
    sortedElements.push_back(lastElemIter->value);

    // Testing operator--
    for (iter = lastElemIter; iter != avlTree.begin(); iter--) {
      EXPECT_EQ(iter->value, sortedElements.back());
      sortedElements.pop_back();
    }
    EXPECT_EQ(iter->value, sortedElements.back());
  }
}

TEST(AVLTree, LowerBound) {
  {
    tree::AVL<int> avlTree;
    avlTree.insert(1);
    avlTree.insert(2);
    avlTree.insert(3);
    avlTree.insert(4);
    avlTree.insert(5);
    auto resIter = avlTree.lower_bound(3);
    EXPECT_EQ(resIter->value, 3);
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(-3);
    avlTree.insert(-2);
    avlTree.insert(-1);
    avlTree.insert(0);
    auto resIter = avlTree.lower_bound(0);
    EXPECT_EQ(resIter->value, 0);

    auto checkIter = avlTree.begin();
    for (size_t i = 0; i < 3; ++i)
      checkIter++;
    EXPECT_EQ(resIter->value, checkIter->value);
    EXPECT_EQ(resIter, checkIter);
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(100);
    avlTree.insert(200);
    avlTree.insert(300);
    avlTree.insert(400);

    auto resIter = avlTree.lower_bound(500);
    EXPECT_EQ(resIter, avlTree.end());

    resIter = avlTree.lower_bound(50);
    EXPECT_EQ(resIter, avlTree.begin());

    resIter = avlTree.lower_bound(200);
    auto checkIter = avlTree.begin();
    EXPECT_EQ(resIter, ++checkIter);
  }
}

TEST(AVLTree, UpperBound) {
  {
    tree::AVL<int> avlTree;
    avlTree.insert(1);
    avlTree.insert(2);
    avlTree.insert(3);
    avlTree.insert(4);
    avlTree.insert(5);
    auto resIter = avlTree.upper_bound(3);
    EXPECT_EQ(resIter->value, 4);
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(-3);
    avlTree.insert(-2);
    avlTree.insert(-1);
    avlTree.insert(0);
    auto resIter = avlTree.upper_bound(0);
    EXPECT_EQ(resIter, avlTree.end());
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(100);
    avlTree.insert(200);
    avlTree.insert(300);
    avlTree.insert(400);

    auto resIter = avlTree.upper_bound(500);
    EXPECT_EQ(resIter, avlTree.end());

    resIter = avlTree.upper_bound(300);
    EXPECT_EQ(resIter != avlTree.end(), true);
    EXPECT_EQ(resIter->value, 400);

    resIter = avlTree.upper_bound(100);
    auto checkIter = avlTree.begin();
    EXPECT_EQ(resIter, ++checkIter);
  }
}

TEST(AVLTree, Find) {
  {
    tree::AVL<int> avlTree;
    avlTree.insert(1);
    avlTree.insert(2);
    avlTree.insert(3);
    avlTree.insert(4);
    avlTree.insert(5);
    auto resIter = avlTree.find(3);
    EXPECT_EQ(resIter != avlTree.end(), true);
    EXPECT_EQ(avlTree.find(3), avlTree.lower_bound(3));
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(-3);
    avlTree.insert(-2);
    avlTree.insert(-1);
    avlTree.insert(0);

    auto resIter = avlTree.find(0);
    EXPECT_EQ(resIter != avlTree.end(), true);
    EXPECT_EQ(resIter->value, 0);
    EXPECT_EQ(resIter, avlTree.lower_bound(0));
    EXPECT_EQ(resIter, avlTree.upper_bound(-1));
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(100);
    avlTree.insert(200);
    avlTree.insert(300);
    avlTree.insert(400);

    auto resIter = avlTree.find(500);
    EXPECT_EQ(resIter, avlTree.end());

    resIter = avlTree.lower_bound(300);
    EXPECT_EQ(resIter != avlTree.end(), true);
    EXPECT_EQ(resIter->value, 300);
  }
}

TEST(AVLTree, BruteRangeQuerieCount) {
  tree::AVL<int> avlTree;
  avlTree.insert(10);
  avlTree.insert(20);
  avlTree.insert(30);
  avlTree.insert(40);
  avlTree.insert(50);

  EXPECT_EQ(avlTree.getRangeQuerieCount(29, 41), 2);
  EXPECT_EQ(avlTree.getRangeQuerieCount(40, 50), 2);
  EXPECT_EQ(avlTree.getRangeQuerieCount(39, 50), 2);
  EXPECT_EQ(avlTree.getRangeQuerieCount(41, 50), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(41, 51), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(39, 51), 2);
  EXPECT_EQ(avlTree.getRangeQuerieCount(40, 41), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(50, 51), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(10, 20), 2);
  EXPECT_EQ(avlTree.getRangeQuerieCount(20, 30), 2);
  EXPECT_EQ(avlTree.getRangeQuerieCount(29, 31), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(49, 51), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(9, 11), 1);

  EXPECT_EQ(avlTree.getRangeQuerieCount(10, 10), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(20, 20), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(30, 30), 1);
  EXPECT_EQ(avlTree.getRangeQuerieCount(40, 40), 1);

  EXPECT_EQ(avlTree.getRangeQuerieCount(7, 7), 0);
  EXPECT_EQ(avlTree.getRangeQuerieCount(31, 31), 0);
  EXPECT_EQ(avlTree.getRangeQuerieCount(101, 101), 0);
  EXPECT_EQ(avlTree.getRangeQuerieCount(30, 10), 3);
}

TEST(AVLTree, FastRangeQuerieCountCorrectness) {
  {
    tree::AVL<int> avlTree;
    avlTree.insert(10);
    avlTree.insert(20);
    avlTree.insert(30);
    avlTree.insert(40);
    avlTree.insert(50);

    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(29, 41), 2);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(40, 50), 2);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(39, 50), 2);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(41, 50), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(41, 51), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(39, 51), 2);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(40, 41), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(50, 51), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(10, 20), 2);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(20, 30), 2);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(29, 31), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(49, 51), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(9, 11), 1);

    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(10, 10), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(20, 20), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(30, 30), 1);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(40, 40), 1);

    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(7, 7), 0);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(31, 31), 0);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(101, 101), 0);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(30, 10), 3);

    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(7, 52), 5);
  }

  {
    tree::AVL<int> avlTree;
    avlTree.insert(0);
    avlTree.insert(1);
    avlTree.insert(2);
    avlTree.insert(3);
    avlTree.insert(4);
    avlTree.insert(5);
    avlTree.insert(6);
    avlTree.insert(7);
    avlTree.insert(8);
    avlTree.insert(9);

    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(2, 6), 5);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(3, 8), 6);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(3, 7), 5);
  }

  {
    tree::AVL<int> avlTree;
    EXPECT_EQ(avlTree.size(), 0);
    avlTree.insert(0);
    EXPECT_EQ(avlTree.size(), 1);
    avlTree.insert(2);
    EXPECT_EQ(avlTree.size(), 2);
    avlTree.insert(4);
    EXPECT_EQ(avlTree.size(), 3);
    avlTree.insert(6);
    EXPECT_EQ(avlTree.size(), 4);
    avlTree.insert(8);
    EXPECT_EQ(avlTree.size(), 5);

    avlTree.insert(10);
    EXPECT_EQ(avlTree.size(), 6);
    avlTree.insert(12);
    EXPECT_EQ(avlTree.size(), 7);
    avlTree.insert(14);
    EXPECT_EQ(avlTree.size(), 8);
    avlTree.insert(16);
    EXPECT_EQ(avlTree.size(), 9);
    avlTree.insert(18);
    EXPECT_EQ(avlTree.size(), 10);

    avlTree.insert(20);
    EXPECT_EQ(avlTree.size(), 11);
    avlTree.insert(22);
    EXPECT_EQ(avlTree.size(), 12);
    avlTree.insert(24);
    EXPECT_EQ(avlTree.size(), 13);
    avlTree.insert(26);
    EXPECT_EQ(avlTree.size(), 14);
    avlTree.insert(28);
    EXPECT_EQ(avlTree.size(), 15);

    avlTree.insert(30);
    EXPECT_EQ(avlTree.size(), 16);
    avlTree.insert(32);
    EXPECT_EQ(avlTree.size(), 17);
    avlTree.insert(34);
    EXPECT_EQ(avlTree.size(), 18);
    avlTree.insert(36);
    EXPECT_EQ(avlTree.size(), 19);
    avlTree.insert(38);
    EXPECT_EQ(avlTree.size(), 20);

    avlTree.insert(40);
    EXPECT_EQ(avlTree.size(), 21);
    avlTree.insert(42);
    EXPECT_EQ(avlTree.size(), 22);
    avlTree.insert(44);
    EXPECT_EQ(avlTree.size(), 23);
    avlTree.insert(46);
    EXPECT_EQ(avlTree.size(), 24);
    avlTree.insert(48);
    EXPECT_EQ(avlTree.size(), 25);

    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(9, 9), 0);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(1, 13), 6);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(7, 27), 10);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(7, 20), 7);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(36, 21), 8);
  }
}

TEST(AVLTree, MainMethodCorrectness) {
  tree::Standard stdTree;
  tree::AVL<int> avlTree;

  int border = 13824;
  for (int i = 0; i < border; i++) {
    stdTree.insert(i);
    avlTree.insert(i);
  }

  int N = 100;
  std::vector<int> ranges;
  srand(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < N; i++)
    ranges.push_back(1 + rand() % border);

  for (int i = 0; i < ranges.size() - 2; i++) {
    int correct = stdTree.getRangeQuerieCount(ranges[i], ranges[i + 1]);
    EXPECT_EQ(avlTree.getRangeQuerieCount(ranges[i], ranges[i + 1]), correct);
  }
}

TEST(AVLTree, FastMethodSmallCorectness) {
  tree::Standard stdTree;
  tree::AVL<int> avlTree;

  int border = 50;
  int step = 1 + rand() % (border / 5);
  for (int i = 0; i < border; i += step) {
    stdTree.insert(i);
    avlTree.insert(i);
  }

  int N = 10;
  std::vector<int> ranges;
  srand(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < N; i++)
    ranges.push_back(1 + rand() % border);

  for (int i = 0; i < ranges.size() - 2; i++) {
    int correct = stdTree.getRangeQuerieCount(ranges[i], ranges[i + 1]);
    int res = avlTree.fastGetRangeQuerieCount(ranges[i], ranges[i + 1]);
    if (correct != res)
      std::cout << "(" << ranges[i] << ", " << ranges[i + 1] << ")"
                << std::endl;

    EXPECT_EQ(res, correct);
  }
}

TEST(AVLTree, FastMethodFullCorrectness) {
  tree::Standard stdTree;
  tree::AVL<int> avlTree;

  int border = 13824;
  for (int i = 0; i < border; i++) {
    stdTree.insert(i);
    avlTree.insert(i);
  }

  int N = 100;
  std::vector<int> ranges;
  srand(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < N; i++)
    ranges.push_back(1 + rand() % border);

  for (int i = 0; i < ranges.size() - 2; i++) {
    int correct = stdTree.getRangeQuerieCount(ranges[i], ranges[i + 1]);
    EXPECT_EQ(avlTree.fastGetRangeQuerieCount(ranges[i], ranges[i + 1]),
              correct);
  }
}

#include <chrono>
TEST(AVLTree, Performance) {
  tree::Standard stdTree;
  tree::AVL<int> avlTree;

  int border = 347483;
  for (int i = 0; i < border; i++) {
    stdTree.insert(i);
    avlTree.insert(i);
  }

  int N = 1000;
  std::vector<int> ranges;
  srand(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < N; i++)
    ranges.push_back(1 + rand() % border);

  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ranges.size() - 2; i++)
      stdTree.getRangeQuerieCount(ranges[i], ranges[i + 1]);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "  [STD] Execution time: " << duration.count()
              << " microseconds." << std::endl;
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ranges.size() - 2; i++)
      avlTree.fastGetRangeQuerieCount(ranges[i], ranges[i + 1]);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "  [AVL] Fast execution time: " << duration.count()
              << " microseconds." << std::endl;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
