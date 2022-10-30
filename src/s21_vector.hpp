#ifndef _SRC_S21_VECTOR_HPP_
#define _SRC_S21_VECTOR_HPP_

#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

namespace s21 {

template <class T>
class iterator_vector;

template <class T>
class const_iterator_vector;

template <class T>
class vector {
  // value_type	T defines the type of an element (T is template parameter)
  using value_type = T;

  // pointer T*
  using pointer = T *;

  // reference T & defines the type of the reference to an element
  using reference = T &;

  // const_reference const T & defines the type of the constant reference
  using const_reference = const T &;

  // iterator	T * or internal class VectorIterator<T> defines the type for
  // iterating through the container
  using iterator = iterator_vector<T>;

  // const_iterator const T * or internal class VectorConstIterator<T> defines
  // the constant type for iterating through the container
  using const_iterator = const_iterator_vector<T>;

  // size_type size_t defines the type of the container size (standard type is
  // size_t)
  using size_type = std::size_t;

 private:
  value_type *first_;
  size_type size_;
  size_type alloc_size_;

 public:
  // Constructors, assigment opeartors
  vector() {
    first_ = nullptr;
    size_ = 0;
    alloc_size_ = 0;
  }

  vector(size_type n) {
    first_ = new value_type[n];
    size_ = n;
    alloc_size_ = n;
  }

  vector(std::initializer_list<value_type> const &items) : first_(nullptr) {
    size_ = alloc_size_ = items.size();
    if (size_) {
      first_ = new value_type[size_];
      std::copy(items.begin(), items.end(), first_);
    } else {
      first_ = nullptr;
    }
  }

  vector(const vector &v) : size_(v.size_), alloc_size_(v.alloc_size_) {
    if (size_) {
      first_ = new value_type[size_];
      std::copy(v.first_, v.first_ + (v.size_ - 1), first_);
    } else {
      first_ = nullptr;
    }
  }

  vector(vector &&v) : size_(v.size_), alloc_size_(v.alloc_size_) {
    first_ = v.first_;
    v.first_ = nullptr;
    v.size_ = 0;
    v.alloc_size_ = 0;
  }

  ~vector() {
    if (first_ != nullptr) {
      delete[] first_;
      first_ = nullptr;
    }
    size_ = 0;
    alloc_size_ = 0;
  }

  vector &operator=(const vector &v) {
    if (first_ == v.first_) {
      return *this;
    }

    if (first_ != nullptr) {
      delete[] first_;
    }

    size_ = v.size_;
    alloc_size_ = v.alloc_size_;

    if (size_) {
      first_ = new value_type[alloc_size_];
      std::copy(v.first_, v.first_ + v.size_, first_);
    } else {
      first_ = nullptr;
    }

    return *this;
  }

  vector &operator=(vector &&v) noexcept {
    if (this == v) {
      return *this;
    }

    if (first_ != nullptr) {
      delete[] first_;
    }

    first_ = v.first_;
    size_ = v.size_;
    alloc_size_ = v.alloc_size_;

    v.first_ = nullptr;
    v.alloc_size_ = v.size_ = 0;
    return *this;
  }

  // Methods for acces of elements

  // access specified element with bounds checking
  reference at(size_type pos) {
    if (pos < 0 || pos > size_ - 1)
      throw std::out_of_range("index out of range");
    return *(first_ + pos);
  }

  // access specified element
  reference operator[](size_type pos) { return *(first_ + pos); }

  //	access the first element
  const_reference front() const { return *first_; }

  // access the last element
  const_reference back() const { return *(first_ + size_ - 1); }

  // direct access to the underlying array
  T *data() { return first_; }

  // Iterators
  iterator begin() { return iterator(first_); }
  iterator end() { return iterator(first_ + size_); }

  const_iterator begin() const { return const_iterator(first_); }
  const_iterator end() const { return const_iterator(first_ + size_); }

  // Methods for capacity

  // checks whether the container is empty
  [[nodiscard]] bool empty() const {
    if (size_ == 0) {
      return true;
    }
    return false;
  }

  // returns the number of elements
  [[nodiscard]] size_type size() const { return size_; }

  // returns the maximum possible number of elements
  [[nodiscard]] size_type max_size() {
    return alloc_size_ * sizeof(value_type);
  }

  // allocate storage of size elements and copies current array elements to a
  // newely allocated array
  void reserve(size_type size) {
    if (size > alloc_size_) {
      alloc_size_ = size;
      T *reallocated = new T[alloc_size_];
      std::memcpy(reallocated, first_, size_ * sizeof(T));
      delete[] first_;
      first_ = reallocated;
    }
  }

  // returns the number of elements that can be held in currently allocated
  // storage
  size_type capacity() const { return alloc_size_; }

  // reduces memory usage by freeing unused memory
  void shrink_to_fit() {
    if (alloc_size_ > size_) {
      alloc_size_ = size_;
      T *reallocated = new T[alloc_size_];
      std::memmove(reallocated, first_, size_ * sizeof(T));
      delete[] first_;
      first_ = reallocated;
    }
  }

  // Methods for changing container

  // clears the contents
  void clear() { this->~vector(); }

  // inserts elements into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value) {
    size_++;
    if (first_ == nullptr) {
      alloc_size_ = 1;
      first_ = new value_type[alloc_size_];
      *first_ = value;
      return iterator(first_);
    }

    if (size_ <= alloc_size_) {
      std::memmove(pos.ptr_ + 1, pos.ptr_,
                   (size_ - 1) * sizeof(T) - (pos.ptr_ - first_) * sizeof(T));
      *(pos.ptr_) = value;
      return iterator(pos);
    } else {
      alloc_size_ *= 2;
      pointer reallocated = new T[alloc_size_];

      std::memmove(reallocated, first_, (size_ - 1) * sizeof(T));
      size_type p = pos.ptr_ - first_;
      delete[] first_;

      first_ = reallocated;

      if (p != size_ - 1) {
        std::memmove(first_ + p + 1, first_ + p, (size_ - 1 - p) * sizeof(T));
      }

      *(first_ + p) = value;
      return iterator(first_ + p);
    }
  }

  // erases element at pos
  void erase(iterator pos) {
    if (first_ == nullptr) {
      return;
    }

    std::memmove(pos.ptr_, pos.ptr_ + 1,
                 (size_ - 1) * sizeof(value_type) -
                     (pos.ptr_ - first_) * sizeof(value_type));
    size_--;
  }

  // adds an element to the end
  void push_back(const_reference value) { this->insert(this->end(), value); }

  // removes the last element
  void pop_back() {
    if (size_ == 0) return;
    size_--;
  }

  // swaps the contents
  void swap(vector &other) {
    std::swap(other.size_, size_);
    std::swap(other.alloc_size_, alloc_size_);
    std::swap(other.first_, first_);
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    value_type val(args...);
    return this->insert(pos, val);
  }

  template <class... Args>
  iterator emplace_back(Args &&...args) {
    value_type val(args...);
    return this->insert(this->end(), val);
  }
};

template <class T>
class iterator_vector {
  friend class vector<T>;
  friend class const_iterator_vector<T>;

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T *;
  using reference = T &;

  pointer ptr_;

 public:
  iterator_vector() : ptr_(nullptr){};
  iterator_vector(pointer ptr) : ptr_(ptr){};
  value_type &operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  iterator_vector &operator++() {
    ptr_++;
    return *this;
  }

  iterator_vector &operator--() {
    ptr_--;
    return *this;
  }

  iterator_vector operator++(int) {
    iterator_vector tmp = *this;
    ++(*this);
    return tmp;
  }

  iterator_vector operator--(int) {
    iterator_vector tmp = *this;
    --(*this);
    return tmp;
  }

  friend bool operator==(const iterator_vector &a, const iterator_vector &b) {
    return a.ptr_ == b.ptr_;
  }

  friend bool operator!=(const iterator_vector &a, const iterator_vector &b) {
    return a.ptr_ != b.ptr_;
  }

  operator const_iterator_vector<T>() const {
    return const_iterator_vector<T>(ptr_);
  }
};

template <class T>
class const_iterator_vector {
  friend class vector<T>;
  friend class iterator_vector<T>;

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T *;  // or also value_type*
  using reference = T &;

  pointer ptr_;

 public:
  const_iterator_vector() : ptr_(nullptr){};
  const_iterator_vector(pointer ptr) : ptr_(ptr){};
  value_type operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  const_iterator_vector &operator++() {
    ptr_++;
    return *this;
  }

  const_iterator_vector &operator--() {
    ptr_--;
    return *this;
  }

  const_iterator_vector operator++(int) {
    const_iterator_vector tmp = *this;
    ++(*this);
    return tmp;
  }

  const_iterator_vector operator--(int) {
    const_iterator_vector tmp = *this;
    --(*this);
    return tmp;
  }

  friend bool operator==(const const_iterator_vector &a,
                         const const_iterator_vector &b) {
    return a.ptr_ == b.ptr_;
  }

  friend bool operator!=(const const_iterator_vector &a,
                         const const_iterator_vector &b) {
    return a.ptr_ != b.ptr_;
  }

  operator iterator_vector<T>() const { return iterator_vector<T>(ptr_); }
};

}  // namespace s21

#endif  // _SRC_S21_VECTOR_HPP_