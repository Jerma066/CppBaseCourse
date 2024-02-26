#pragma once

#include <iostream>
#include <numeric>
#include <tuple>

namespace nums {

class Rational final {
public:
  Rational(long long numerator = 0, long long denominator = 1) {
    std::tie(numer, denom) = processRationalPair(numerator, denominator);
  }

public:
  long long getNumerator() const { return numer; }
  long long getDenominator() const { return denom; }

public:
  static std::tuple<long long, long long>
  processRationalPair(long long numerator, long long denominator);

  bool equal(const Rational& rhs) const {
    return (numer == rhs.numer) && (denom == rhs.denom);
  }

  void dump(std::basic_ostream<char> &OS = std::cout) {
    OS << numer << "/" << denom;
  }

public:
  operator double() const {
    return static_cast<double>(numer) / denom;
  }

  // TODO: Maybe it will be better to use std::gcd to create
  //       lower common denominator and numerator
  Rational& operator+=(const Rational& rhs) {
    long long newNumer = numer * rhs.denom + denom * rhs.numer;
    long long commonDenom = denom * rhs.denom;
    std::tie(numer, denom) = processRationalPair(newNumer, commonDenom);
    return *this;
  }

  Rational &operator-=(const Rational &rhs);
  Rational &operator*=(const Rational &rhs);
  Rational &operator/=(const Rational &rhs);

private:
	long long numer;
	long long denom;
};

} // namespace nums

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &OS,
                                     nums::Rational &rnum);

// Binary operators
nums::Rational operator+(const nums::Rational& lhs,
                         const nums::Rational& rhs);

nums::Rational operator-(const nums::Rational& lhs,
                         const nums::Rational& rhs);

nums::Rational operator*(const nums::Rational& lhs,
                         const nums::Rational& rhs);

nums::Rational operator/(const nums::Rational& lhs,
                         const nums::Rational& rhs);

nums::Rational operator==(const nums::Rational& lhs,
                          const nums::Rational& rhs);

nums::Rational operator!=(const nums::Rational& lhs,
                          const nums::Rational& rhs);
