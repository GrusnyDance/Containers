#ifndef _SRC_S21_ARRAY_HPP_
#define _SRC_S21_ARRAY_HPP_

#include <iostream>  // DEBUG

namespace s21 {
template <typename T, std::size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

 private:
  size_type size_ = N;
  value_type arr_[N];

 public:
  // конструкторы
  Array() {}
  Array(std::initializer_list<value_type> const &items) {
    iterator temp = arr_;
    for (auto i : items) {
      *temp = i;
      ++temp;
    }
    auto count = N - items.size();
    while (count > 0) {
      *temp = T();
      ++temp;
      --count;
    }
  }
  Array(const Array &other) = default;
  Array(Array &&other) = default;
  ~Array() {}
  // скорее всего тут работает и дефолтный
  void operator=(Array &&a) { std::move(a.begin(), a.end(), arr_); }

  reference at(size_type pos) {
    if (pos > size_ - 1 || pos < 0) {
      throw std::out_of_range("Index is not available");
    } else {
      return arr_[pos];
    }
  }

  reference operator[](size_type pos) { return *(arr_ + pos); }
  const_reference front() const { return arr_[0]; }
  const_reference back() const { return arr_[size_ - 1]; }

  iterator data() { return arr_; }
  iterator begin() { return arr_; }
  iterator end() { return arr_ + size_; }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return size_; };

  void swap(Array &other) {
    if (arr_ == other.arr_) return;
    if (size_ != other.size_)
      throw std::out_of_range("Sizes of arrays are not same");

    std::swap(*this, other);
  }

  void fill(const_reference value) {
    if (!size_) return;
    iterator temp = arr_;
    for (temp = begin(); temp != end(); ++temp) {
      *temp = value;
    }
  }
};
}  // namespace s21

#endif  // _SRC_S21_ARRAY_HPP_