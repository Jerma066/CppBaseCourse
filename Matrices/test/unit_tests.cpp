#include <gtest/gtest.h>

#include "matrix.hpp"
#include "myvector.hpp"
#include "rational.h"

// ----- Rational tests -------------------------------------------------------
TEST(Rational, Constructor) {
  {
    nums::Rational rNum(10, 20);
    EXPECT_EQ(rNum.getNumerator(), 1);
    EXPECT_EQ(rNum.getDenominator(), 2);
    EXPECT_EQ(static_cast<double>(rNum), 0.5d);
  }
  {
    nums::Rational rNum(13, 19);
    EXPECT_EQ(rNum.getNumerator(), 13);
    EXPECT_EQ(rNum.getDenominator(), 19);
  }
  {
    nums::Rational rNum(0, 127);
    EXPECT_EQ(rNum.getNumerator(), 0);
    EXPECT_EQ(rNum.getDenominator(), 1);
  }
  {
    nums::Rational rNum(-1, 5);
    EXPECT_EQ(rNum.getNumerator(), -1);
    EXPECT_EQ(rNum.getDenominator(), 5);
    EXPECT_EQ(static_cast<double>(rNum), -0.2d);
  }
  {
    nums::Rational rNum(-7, -21);
    EXPECT_EQ(rNum.getNumerator(), 1);
    EXPECT_EQ(rNum.getDenominator(), 3);
  }
  {
    nums::Rational rNum(15, -8);
    EXPECT_EQ(rNum.getNumerator(), -15);
    EXPECT_EQ(rNum.getDenominator(), 8);
  }
}

TEST(Rational, Addition) {
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(1, 4);
    nums::Rational sumRNum = lhsRNum + rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 7);
    EXPECT_EQ(sumRNum.getDenominator(), 12);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(2, 3);
    nums::Rational sumRNum = lhsRNum + rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 1);
    EXPECT_EQ(sumRNum.getDenominator(),1);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(-1, 3);
    nums::Rational sumRNum = lhsRNum + rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 0);
    EXPECT_EQ(sumRNum.getDenominator(), 1);
  }
}

TEST(Rational, Subtraction) {
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(1, 4);
    nums::Rational sumRNum = lhsRNum - rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 1);
    EXPECT_EQ(sumRNum.getDenominator(), 12);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(1, 3);
    nums::Rational sumRNum = lhsRNum - rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 0);
    EXPECT_EQ(sumRNum.getDenominator(), 1);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(-2, 3);
    nums::Rational sumRNum = lhsRNum - rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 1);
    EXPECT_EQ(sumRNum.getDenominator(), 1);
  }
}

TEST(Rational, Multiplication) {
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(1, 4);
    nums::Rational sumRNum = lhsRNum * rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 1);
    EXPECT_EQ(sumRNum.getDenominator(), 12);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(3, 1);
    nums::Rational sumRNum = lhsRNum * rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 1);
    EXPECT_EQ(sumRNum.getDenominator(), 1);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(3, -1);
    nums::Rational sumRNum = lhsRNum * rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), -1);
    EXPECT_EQ(sumRNum.getDenominator(), 1);
  }
  {
    nums::Rational lhsRNum(0, 3);
    nums::Rational rhsRNum(-2, 3);
    nums::Rational sumRNum = lhsRNum * rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 0);
    EXPECT_EQ(sumRNum.getDenominator(), 1);
  }
}

TEST(Rational, Division) {
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(1, 4);
    nums::Rational sumRNum = lhsRNum / rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 4);
    EXPECT_EQ(sumRNum.getDenominator(), 3);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(1, 3);
    nums::Rational sumRNum = lhsRNum / rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), 1);
    EXPECT_EQ(sumRNum.getDenominator(), 1);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(-5, 1);
    nums::Rational sumRNum = lhsRNum / rhsRNum;
    EXPECT_EQ(sumRNum.getNumerator(), -1);
    EXPECT_EQ(sumRNum.getDenominator(), 15);
  }
}

TEST(Rational, Equality) {
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(1, 4);
    EXPECT_EQ(lhsRNum == rhsRNum, false);
    EXPECT_EQ(lhsRNum != rhsRNum, true);
  }
  {
    nums::Rational lhsRNum(1, 3);
    nums::Rational rhsRNum(1, 3);
    EXPECT_EQ(lhsRNum == rhsRNum, true);
    EXPECT_EQ(lhsRNum != rhsRNum, false);
  }
  {
    nums::Rational lhsRNum(-1, 3);
    nums::Rational rhsRNum(1, -3);
    EXPECT_EQ(lhsRNum == rhsRNum, true);
    EXPECT_EQ(lhsRNum != rhsRNum, false);
  }
  {
    nums::Rational lhsRNum(-1, 3);
    nums::Rational rhsRNum(5, -15);
    EXPECT_EQ(lhsRNum == rhsRNum, true);
    EXPECT_EQ(lhsRNum != rhsRNum, false);
  }
}

// ----- MyVector tests -------------------------------------------------------
TEST(MyVector, Constructor) {
  {
    mystd::MyVector<int> vec(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 5);

    mystd::MyVector<int> cvec(vec);
    EXPECT_EQ(cvec.size(), 5);
    EXPECT_EQ(cvec.capacity(), 5);

    mystd::MyVector<int> mvec(std::move(vec));
    EXPECT_EQ(mvec.size(), 5);
    EXPECT_EQ(mvec.capacity(), 5);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
  }

  {
    mystd::MyVector<int> vec({1, 2, 3, 4, 5});
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 5);
  }
}

TEST(MyVector, Assigment) {
  {
    mystd::MyVector<float> vec(3);
    
    mystd::MyVector<float> cvec = vec;
    EXPECT_EQ(cvec.size(), 3);
    EXPECT_EQ(cvec.capacity(), 3);

    mystd::MyVector<float> mvec = std::move(vec);
    EXPECT_EQ(mvec.size(), 3);
    EXPECT_EQ(mvec.capacity(), 3);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
  }
  {
    mystd::MyVector<float> vec = {1.0, 2.0, 3.0};
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 3);
  }
}

TEST(MyVector, SquareBracketsOperator) {
  {
    mystd::MyVector<double> vec = {1.0, 2.0, 3.0};
    EXPECT_EQ(vec[0], 1.0);
    EXPECT_EQ(vec[1], 2.0);
    EXPECT_EQ(vec[2], 3.0);    
  }
  {
    const mystd::MyVector<double> vec = {1.0, 2.0, 3.0};
    EXPECT_EQ(vec[0], 1.0);
    EXPECT_EQ(vec[1], 2.0);
    EXPECT_EQ(vec[2], 3.0);
  }
  {
    mystd::MyVector<char> vec = {'a', 'b', 'c', 'd', 'f'};
    try {
      vec[5];
    } catch (const std::runtime_error& e) {
      EXPECT_TRUE(true);
    }
  }
}

TEST(MyVector, BackPopPush) {
  {
    mystd::MyVector<size_t> vec = {37};
    EXPECT_EQ(vec.back(), 37);
  }
  {
    mystd::MyVector<long long> vec;
    try {
      vec.back();
    } catch (const std::runtime_error& e) {
      EXPECT_TRUE(true);
    }
  }
  {
    mystd::MyVector<long long> vec = {1, 2};
    EXPECT_EQ(vec.back(), 2);
    vec.pop_back();
    EXPECT_EQ(vec.back(), 1);
    vec.pop_back();
    try {
      vec.pop_back();
    } catch (const std::runtime_error& e) {
      EXPECT_TRUE(true);
    }
  }
  {
    mystd::MyVector<char> vec = {'K', 'A', 'M', 'I'};
    EXPECT_EQ(vec.back(), 'I');
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 4);

    vec.push_back('N');
    vec.push_back('N');
    EXPECT_EQ(vec.back(), 'N');
    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec.capacity(), 9);

    vec.pop_back();
    EXPECT_EQ(vec.back(), 'N');
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 9);
  }
}
// ----- Matrices tests -------------------------------------------------------
TEST(Matrix, Constructor) {
  {
    linalg::Matrix<nums::Rational> mtr(3);
    EXPECT_EQ(mtr.size(), 3);
  }
  {
    // CopyCtor
    linalg::Matrix<nums::Rational> mtr(3);
    EXPECT_EQ(mtr.size(), 3);
    mtr.mData = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    linalg::Matrix<nums::Rational> copyMtr = mtr;

    EXPECT_EQ(copyMtr.mData[0][0], 1);
    EXPECT_EQ(copyMtr.mData[0][1], 2);
    EXPECT_EQ(copyMtr.mData[0][2], 3);

    EXPECT_EQ(copyMtr.mData[1][0], 4);
    EXPECT_EQ(copyMtr.mData[1][1], 5);
    EXPECT_EQ(copyMtr.mData[1][2], 6);

    EXPECT_EQ(copyMtr.mData[2][0], 7);
    EXPECT_EQ(copyMtr.mData[2][1], 8);
    EXPECT_EQ(copyMtr.mData[2][2], 9);
  }
  {
    size_t mSize = 3;
    auto mtr = linalg::makeEMatrix<int>(mSize);
    EXPECT_EQ(mtr.size(), mSize);
    for (size_t i = 0; i < mSize; ++i) {
      for (size_t j = 0; j < mSize; ++j) {
        int expVal = (i == j) ? 1 : 0;
        EXPECT_EQ(mtr[i][j], expVal);
      }
    }
  }
}

TEST(Matrix, SquareBracketsOperator) {
  {
    linalg::Matrix<nums::Rational> mtr(3);
    EXPECT_EQ(mtr.size(), 3);
    mtr[1] = {3, 4, 5};
    EXPECT_EQ(mtr[1].size(), 3);
    EXPECT_EQ(mtr[1][0], 3);
    EXPECT_EQ(mtr[1][1], 4);
    EXPECT_EQ(mtr[1][2], 5);
  }
}

TEST(Matrix, GaussDeterminant) {
  {
    size_t mSize = 3;
    auto mtr = linalg::makeEMatrix<int>(mSize);
    int det = mtr.GaussDet();
    EXPECT_EQ(det, 1);
  }
  {
    linalg::Matrix<int> mtr(2);
    mtr[0] = {1, 1};
    mtr[1] = {1, 1};
    int det = mtr.GaussDet();
    EXPECT_EQ(det, 0);
  }
  {
    linalg::Matrix<double> mtr(3);
    mtr[0] = {3, 21, 5};
    mtr[1] = {1, 8, 7};
    mtr[2] = {9, 47, 54};
    double det = mtr.GaussDet();
    EXPECT_EQ(det, 373.0);
  }
  {
    linalg::Matrix<nums::Rational> mtr(2);
    mtr[0] = {nums::Rational(1), nums::Rational(1)};
    mtr[1] = {nums::Rational(1), nums::Rational(1)};
    nums::Rational det = mtr.GaussDet();
    EXPECT_EQ(static_cast<double>(det), 0.0);
  }
}

// ----------------------------------------------------------------------------
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
