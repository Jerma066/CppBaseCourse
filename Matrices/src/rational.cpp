#include "rational.h"

namespace nums {

std::tuple<long long, long long>
  Rational::processRationalPair(long long numerator, long long denominator) {
  // TODO: Handle cases where denoumerator equal to zero
  //       Handle cases where numerators value equal to long long max
  //       scince it can be multiplied by -1 and exceed the limit
  if (numerator == 0)
    denominator = 1;

  // Getting rid of excessive negativity;
  // Move sign to numerator if exists
  if (denominator < 0) {
    numerator *= -1;
    denominator *= -1;
  }

  // Reducing input values using std::gcd
  long long divisor = std::gcd(numerator, denominator);
  return std::make_tuple(numerator / divisor, denominator / divisor);
};

} // namespace nums

// Binary operators
nums::Rational operator+(const nums::Rational& lhs,
                         const nums::Rational& rhs) {
  nums::Rational tmp(lhs);
  tmp += rhs;
  return tmp;
}

nums::Rational operator-(const nums::Rational& lhs,
                         const nums::Rational& rhs) {
  nums::Rational tmp(lhs);
  tmp -= rhs;
  return tmp;
}

nums::Rational operator*(const nums::Rational& lhs,
                         const nums::Rational& rhs) {
  nums::Rational tmp(lhs);
  tmp *= rhs;
  return tmp;
}

nums::Rational operator/(const nums::Rational& lhs,
                         const nums::Rational& rhs) {
  nums::Rational tmp(lhs);
  tmp /= rhs;
  return tmp;
}

nums::Rational operator==(const nums::Rational& lhs,
                          const nums::Rational& rhs) {
  return lhs.equal(rhs);
}

nums::Rational operator!=(const nums::Rational& lhs,
                          const nums::Rational& rhs) {
  return !lhs.equal(rhs);
}

