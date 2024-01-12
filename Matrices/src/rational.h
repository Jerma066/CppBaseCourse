#pragma once

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

public:
  operator double() const {
    return static_cast<double>(numer) / denom;
  }

  // TODO: Maybe it will be better to use std::gcd to create
  //       lower common denominator and numerator
  Rational& operator+=(const Rational& rhs) {
    long long newNumer = numer * rhs.denom + denom * rhs.numer;
    long long commonDenom = denom * rhs.getDenominator();
    std::tie(numer, denom) = processRationalPair(newNumer, commonDenom);
    return *this;
  }

  Rational& operator-=(const Rational& rhs) {
    long long newNumer = numer * rhs.denom - denom * rhs.numer;
    long long commonDenom = denom * rhs.getDenominator();
    std::tie(numer, denom) = processRationalPair(newNumer, commonDenom);
    return *this;
  }

  Rational& operator*=(const Rational& rhs) {
    long long newNumer = numer * rhs.numer; 
    long long newDenom = denom * rhs.denom;
    std::tie(numer, denom) = processRationalPair(newNumer, newDenom);
    return *this;
  }

  Rational& operator/=(const Rational& rhs) {
    // TODO: Zero rhs should be handled
    long long newNumer = numer * rhs.denom;
    long long newDenom = denom * rhs.numer;
    std::tie(numer, denom) = processRationalPair(newNumer, newDenom);
    return *this;
  }

private:
	long long numer;
	long long denom;
};

} // namespace nums

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
