#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "rational.h"

struct Checker {
  int num;
  int denum;
};

int main() {
  std::cout << std::setprecision(16);
  size_t N;
  std::cin >> N;
  linalg::Matrix<Checker> mtr(N);

  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      int num;
      std::cin >> num;
      mtr[i][j] = nums::Rational(num);
    }
  }

  std::cout << mtr.GaussDet() << std::endl;
  return 0;
}
