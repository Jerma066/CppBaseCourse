#pragma once

#include <vector>

namespace linalg {

// TODO: Add checkers that DataType has required operators
template <typename DataType> struct Matrix final {
public:
  explicit Matrix(size_t n)
      : mData(std::vector<std::vector<DataType>>(n, std::vector<DataType>(n))) {
  }

public:
  size_t size() const { return mData.size(); }

  std::tuple<Matrix, bool> GaussElementaryTransform() const {
    Matrix<DataType> tmp = *this;
    bool inverse = false;

    for (size_t i = 0, end = mData.size(); i < mData.size(); ++i) {
      size_t row = i;

      // TODO: There is a search pattern in this for.
      //       It should be replaced with std::find.
      for (size_t j = row, end = mData.size(); j < mData.size(); ++j) {
        if (tmp[i][j] != DataType(0)) {
          row = j;
          break;
        }
      }

      std::swap(tmp[i], tmp[row]);
      if (i != row)
        inverse = !inverse;

      // Getting rid of all elements under current tmp[i, j];
      for (size_t j = i + 1, end = mData.size(); j < end; ++j) {
        if (tmp[j][i] == DataType(0))
          continue;
        DataType q = tmp[j][i] / tmp[i][i];
        for (size_t k = i, end = mData.size(); k < end; ++k)
          tmp[j][k] -= q * tmp[i][k];
      }
    }

    return std::make_tuple(tmp, inverse);
  }

  DataType GaussDet() const {
    auto [tmpMtr, inverse] = GaussElementaryTransform();

    DataType det(1);
    if (inverse)
      det = -det;

    for (size_t i = 0, end = mData.size(); i < end; ++i)
      det *= tmpMtr[i][i];

    return det;
  }

public:
  std::vector<DataType> &operator[](size_t i) {
    if (i > mData.size())
      throw std::invalid_argument("Row index is out of range!");

    return mData[i];
  }

  std::vector<std::vector<DataType>> mData;
};

template <typename DataType> Matrix<DataType> makeEMatrix(size_t n) {
  Matrix<DataType> tmp(n);
  for (size_t i = 0; i < n; ++i) {
    tmp[i] = std::vector<DataType>(n, DataType(0));
    tmp[i][i] = DataType(1);
  }
  return tmp;
}

} // namespace linalg
