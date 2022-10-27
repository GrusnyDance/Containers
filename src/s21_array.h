#include <iostream>  // DEBUG

namespace s21 {
template <typename T, std::size_t N = 0>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

 private:
  size_type size_;
  value_type arr_[size_];

 public:
  // конструкторы
  Array() : size_(N) {
    iterator temp = arr_;
    for (auto i : temp) {
      *i = 0;
    }
  }
  Array(std::initializer_list<value_type> const &items) : Array() {
    size_ = items.size();
    iterator temp = arr_;
    for (auto i : items) {
      *temp = *i;  // мб нужно без разыменования
      ++temp;
    }
  }
  Array(const Array &other) = default;
  Array(Array &&other) = default;
  ~Array() {}
  // скорее всего тут работает и дефолтный
  operator=(Array &&a) { std::move(other.cbegin(), other.cend(), arr_); }

  reference at(size_type pos) const {
    if (pos > size_ - 1 || pos < 0) {
      throw std::out_of_range("Index is not available");
    } else {
      return arr_[pos];
    }
  }

  reference operator[](size_type pos) { return *(arr_ + pos); }
  reference operator[](size_type pos) const { return arr_[pos]; }
  const_reference front() const { return data_[0]; }
  const_reference back() const { return data_[size_ - 1]; }

  iterator data() const { return arr_; }
  iterator begin() const { return arr_; }
  iterator end() const { return arr_ + size_; }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return size_; };

  void swap(array &other) {
    if (arr_ == other.arr_) return;
    if (size_ != other.size_)
      throw std::out_of_range("Sizes of arrays are not same");

    std::swap(*this, other);
  }

  void fill(const_reference value) {
    if (!size_) return;
    iterator temp = arr_;
    for (auto i : temp) {
      *i = value;
    }
  }
};
}  // namespace s21