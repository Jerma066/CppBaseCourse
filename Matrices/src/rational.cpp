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

Rational &Rational::operator-=(const Rational &rhs) {
  long long nngcd = std::gcd(numer, rhs.numer);
  nngcd = (nngcd == 0) ? 1 : nngcd;
  long long ddgcd = std::gcd(denom, rhs.denom);

  long long newNumer = (numer / nngcd) * (rhs.denom / ddgcd) -
                       (denom / ddgcd) * (rhs.numer / nngcd);
  long long commonDenom = (denom / ddgcd) * (rhs.denom / ddgcd);

  long long newGcd = std::gcd(newNumer, commonDenom);
  newNumer /= newGcd;
  commonDenom /= newGcd;

  std::tie(numer, denom) =
      processRationalPair(newNumer * nngcd, commonDenom * ddgcd);
  return *this;
}

Rational &Rational::operator*=(const Rational &rhs) {
  // TODO: ndGcd and dnGcd should be checked with equality to zero
  long long ndGcd = std::gcd(numer, rhs.denom);
  long long dnGcd = std::gcd(denom, rhs.numer);

  long long newNumer = (numer / ndGcd) * (rhs.numer / dnGcd);
  long long newDenom = (denom / dnGcd) * (rhs.denom / ndGcd);

  std::tie(numer, denom) = processRationalPair(newNumer, newDenom);
  return *this;
}

Rational &Rational::operator/=(const Rational &rhs) {
  // TODO: Zero rhs should be handled
  // TODO: nnGcd should be checked with equality to zero
  long long nnGcd = std::gcd(numer, rhs.numer);
  long long ddGcd = std::gcd(denom, rhs.denom);

  long long newNumer = (numer / nnGcd) * (rhs.denom / ddGcd);
  long long newDenom = (denom / ddGcd) * (rhs.numer / nnGcd);

  std::tie(numer, denom) = processRationalPair(newNumer, newDenom);
  return *this;
}

} // namespace nums

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &OS,
                                     nums::Rational &rnum) {
  rnum.dump(OS);
  return OS;
}

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

// TODO: Ugly hack to use std::abs for custom calss in my Matrix
nums::Rational std::abs(const nums::Rational &ratNum) {
  nums::Rational res(std::abs(ratNum.getNumerator()), ratNum.getDenominator());
  return res;
}
