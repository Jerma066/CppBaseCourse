#pragma once

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace mystd {

template <typename MVBType> struct MyVectorBuf {
protected:
  MyVectorBuf(const MyVectorBuf &buf) = delete;
  MyVectorBuf &operator=(const MyVectorBuf &buf) = delete;

  explicit MyVectorBuf(size_t size = 0) {
    // Allocate memory if required
    arr_ = nullptr;
    if (size != 0) // C++ malloc
      arr_ = static_cast<MVBType *>(::operator new(sizeof(MVBType) * size));

    size_ = size;
    used_ = 0;
  }

  MyVectorBuf(MyVectorBuf &&buf)
      : arr_(buf.arr_), size_(buf.size_), used_(buf.used_) {
    buf.arr_ = nullptr;
    buf.size_ = 0;
    buf.used_ = 0;
  }

  MyVectorBuf &operator=(MyVectorBuf &&rhs) {
    std::swap(arr_, rhs.arr_);
    std::swap(size_, rhs.size_);
    std::swap(used_, rhs.used_);
    return *this;
  }

  virtual ~MyVectorBuf() {
    // Destroying objects
    auto curIter = arr_;
    auto endIter = arr_ + used_;
    while (curIter != endIter)
      (curIter++)->~MVBType();

    // Deallocate memory; C++ free
    ::operator delete(arr_);
  }

protected:
  MVBType *arr_;
  size_t size_;
  size_t used_;
};

// TODO: Add class Iterator to support range-based for loops;
//       Add constructor with default value;
template <typename MVType> class MyVector final : private MyVectorBuf<MVType> {
  using MyVectorBuf<MVType>::arr_;
  using MyVectorBuf<MVType>::size_;
  using MyVectorBuf<MVType>::used_;

public:
  explicit MyVector(size_t size = 0) : MyVectorBuf<MVType>(size) {
    while (used_ < size) {
      new (arr_ + used_) MVType();
      used_++;
    }
  }

  MyVector(size_t size, const MVType &defVal) : MyVectorBuf<MVType>(size) {
    while (used_ < size) {
      new (arr_ + used_) MVType(defVal);
      used_++;
    }
  }

  MyVector(MyVector &&vec) = default;
  MyVector &operator=(MyVector &&rhs) = default;

  MyVector(const MyVector &rhs) : MyVectorBuf<MVType>(rhs.used_) {
    while (used_ < rhs.used_) {
      new (arr_ + used_) MVType(rhs.arr_[used_]);
      used_++;
    }
  }

  MyVector &operator=(const MyVector &rhs) {
    MyVector tmp(rhs);
    std::swap(*this, tmp);
    return *this;
  }

  MyVector(std::initializer_list<MVType> values) : MyVectorBuf<MVType>(values.size()) {
    for (auto& value : values) {
      new (arr_ + used_) MVType(value);
      used_++;
    }
  }

  MyVector &operator=(std::initializer_list<MVType> values) {
    MyVector tmp(values);
    std::swap(*this, tmp);
    return *this;
  }

  MVType &operator[](size_t idx) {
    if (idx > used_)
      throw std::runtime_error("Index out of range");
    return arr_[idx];
  }

  const MVType &operator[](size_t idx) const {
    if (idx > used_)
      throw std::runtime_error("Index out of range");
    return arr_[idx];
  }

public:
  MVType back() const {
    if (used_ < 1)
      throw std::runtime_error(
          "There are no elements to call \"back()\" method");
    return arr_[used_ - 1];
  }

  void pop_back() {
    if (used_ < 1)
      throw std::runtime_error(
          "There are no elements to call \"pop_back()\" method");
    used_--;
    (arr_ + used_)->~MVType();
  }

  void push_back(const MVType &elem) {
    MVType tmp(elem);
    push_back(std::move(tmp));
  }

  void push_back(const MVType &&elem) {
    assert(used_ <= size_);

    if (used_ == size_) {
      // Reallocation
      MyVector tmp(size_ * 2 + 1);
      tmp.used_ = 0;
      while (tmp.used_ < used_)
        tmp.push_back(std::move(arr_[used_]));

      tmp.push_back(std::move(elem));
      std::swap(*this, tmp);
    } else {
      new (arr_ + used_) MVType(std::move(elem));
      used_++;
    }
  }

  size_t size() const { return used_; }
  size_t capacity() const { return size_; }
};

} // namespace mystd
