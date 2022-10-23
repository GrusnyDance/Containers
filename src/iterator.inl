// #include "map.hpp"

namespace s21 {
template <typename Data, bool isConst>
TreeIterator<Data, isConst>& TreeIterator<Data, isConst>::operator=(
    const TreeIterator& other) {
  ptr_ = other.ptr_;
  return *this;
}

template <typename Data, bool isConst>
TreeIterator<Data, isConst> TreeIterator<Data, isConst>::operator++(int) {
  TreeIterator before(*this);
  ++(*this);
  return before;
}

template <typename Data, bool isConst>
TreeIterator<Data, isConst> TreeIterator<Data, isConst>::operator--(int) {
  TreeIterator before(*this);
  --(*this);
  return before;
}

template <typename Data, bool isConst>
TreeIterator<Data, isConst>& TreeIterator<Data, isConst>:: operator++() {
  ptr_ = ptr_->nextNode();
  return *this;
}

template <typename Data, bool isConst>
TreeIterator<Data, isConst>& TreeIterator<Data, isConst>:: operator--() {
  ptr_ = ptr_->previousNode();
  return *this;
}

template <typename Data, bool isConst>
bool TreeIterator<Data, isConst>::operator==(const TreeIterator& other) {
  return (ptr_ == other.ptr_);
}

template <typename Data, bool isConst>
bool TreeIterator<Data, isConst>::operator!=(const TreeIterator& other) {
  return (ptr_ != other.ptr_);
}
}  // namespace s21