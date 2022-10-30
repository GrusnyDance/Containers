#ifndef _SRC_S21_QUEUE_HPP_
#define _SRC_S21_QUEUE_HPP_

#include "s21_list.hpp"

namespace s21 {

template <class T>
class queue : protected list<T> {
 private:
  using List = list<T>;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using node = Node<T>;

  queue() : List() {}
  queue(std::initializer_list<value_type> const &items) : List(items) {}
  queue(const queue &q) : List(q) {}
  queue(queue &&q) : List(q) { q.List::del(); }
  queue &operator=(queue &&q) {
    List::operator=(q);
    q.List::del();
    return *this;
  }
  bool operator==(queue other) const { return List::operator==(other); }
  queue &operator=(const queue &q) {
    List::operator=(q);
    return *this;
  }

  const_reference front() { return List::front(); }
  const_reference back() { return List::back(); }
  bool empty() { return List::empty(); }
  size_type size() { return List::size(); }
  void push(const_reference value) { List::push_back(value); }
  void pop() { List::pop_front(); }
  void swap(queue &other) { List::swap(other); }

  template <class... Args>
  void emplace_back(Args &&...args) {
    List::emplace_back(args...);
  }
};
}  // namespace s21

#endif  // _SRC_S21_QUEUE_HPP_
