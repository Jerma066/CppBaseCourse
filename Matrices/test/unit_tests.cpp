#include <gtest/gtest.h>

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
// ----- Matrices tests -------------------------------------------------------

// ----------------------------------------------------------------------------
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
