#pragma once

#include <algorithm>
#include <iostream>
#include <tuple>

#include "myvector.hpp"

namespace linalg {

// TODO: Add checkers that DataType has required operators
template <typename DataType> struct SqMatrix final {
public:
  explicit SqMatrix(size_t n)
      : mData(mystd::MyVector<mystd::MyVector<DataType>>(
            n, mystd::MyVector<DataType>(n))) {}

public:
  size_t size() const { return mData.size(); }

  // TODO: Maybe it will be better to delete this unused function
  /*
  std::tuple<SqMatrix, bool> GaussElementaryTransform() const {
    SqMatrix<DataType> tmp = *this;
    bool inverse = false;

    for (size_t i = 0, end = mData.size(); i < mData.size(); ++i) {
      // Matrix dump
      // tmp.dump();

      const DataType &zeroElem = DataType(0);
      if (tmp[i][i] == zeroElem) {
        auto it = std::find_if(
            tmp.mData.begin() + i, tmp.mData.end(),
            [i, &zeroElem](const mystd::MyVector<DataType> &rowVec) {
              return rowVec[i] != zeroElem;
            });

        if (it != tmp.mData.end()) {
          size_t col = it - tmp.mData.begin();
          if (col != i) {
            std::swap(tmp[i], tmp[col]);
            inverse = !inverse;
          }
        }
      }

      // Getting rid of all elements under current tmp[i, i];
      for (size_t j = i + 1, end = mData.size(); j < end; ++j) {
        if (tmp[j][i] == zeroElem)
          continue;

        DataType q = tmp[j][i] / tmp[i][i];
        tmp[j][i] = 0;
        for (size_t k = i + 1, end = mData.size(); k < end; ++k)
          tmp[j][k] -= q * tmp[i][k];
      }
    }

    return std::make_tuple(tmp, inverse);
  }
  */

  // TODO: Add size check to determine that this is square matrix
  DataType GaussDet() const {
    // Gauss transform
    SqMatrix<DataType> tmp = *this;
    bool inverse = false;
    for (size_t i = 0, end = mData.size(); i < end; ++i) {
      const DataType &zeroElem = DataType(0);
      if (tmp[i][i] == zeroElem) {
        // Searching for non-zero elements in columns
        // TODO: This code contains searching pattern
        //       and can be replced with std::find but
        //       brute implementation seems more readable
        size_t row = i;
        for (size_t j = i + 1, end = tmp.size(); j < end; ++j) {
          if (tmp[j][i] != zeroElem) {
            std::swap(tmp[j], tmp[row]);
            inverse = !inverse;
            break;
          }
        }
      }

      // If there was no non-zero rows -> det = 0
      if (tmp[i][i] == zeroElem)
        return DataType(0);

      // Getting rid of all elements under current tmp[i, i];
      for (size_t j = i + 1, end = mData.size(); j < end; ++j) {
        if (tmp[j][i] == zeroElem)
          continue;

        DataType q = tmp[j][i] / tmp[i][i];
        tmp[j][i] = 0;
        for (size_t k = i + 1, end = mData.size(); k < end; ++k)
          tmp[j][k] -= q * tmp[i][k];
      }
    }

    // Determinant counting
    DataType det(inverse ? -1 : 1);
    for (size_t i = 0, end = mData.size(); i < end; ++i)
      det *= tmp[i][i];

    return det;
  }

  void dump(std::basic_ostream<char> &OS = std::cout) {
    for (auto &vec : mData) {
      for (auto &elem : vec) {
        OS << elem << ' ';
      }
      OS << '\n';
    }
    OS << '\n';
  }

public:
  mystd::MyVector<DataType> &operator[](size_t i) {
    if (i > mData.size())
      throw std::invalid_argument("Row index is out of range!");

    return mData[i];
  }

public:
  mystd::MyVector<mystd::MyVector<DataType>> mData;
};

template <typename DataType> SqMatrix<DataType> makeSqEMatrix(size_t n) {
  SqMatrix<DataType> tmp(n);
  for (size_t i = 0; i < n; ++i) {
    tmp[i] = mystd::MyVector<DataType>(n, DataType(0));
    tmp[i][i] = DataType(1);
  }
  return tmp;
}

} // namespace linalg
