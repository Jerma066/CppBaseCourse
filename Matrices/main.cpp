#include <cmath>
#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "rational.h"

int main() {
  std::cout << std::setprecision(16);
  size_t N;
  std::cin >> N;
  // linalg::SqMatrix<nums::Rational> mtr(N);
  linalg::SqMatrix<double> mtr(N);

  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      // int num;
      double num;
      std::cin >> num;
      // mtr[i][j] = nums::Rational(num);
      mtr[i][j] = num;
    }
  }

  // rounding by the first character
  double detRes = std::round(mtr.GaussDet() * 10) / 10;
  std::cout << detRes << std::endl;
  return 0;
}
