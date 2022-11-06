#ifndef _SRC_S21_SET_HPP_
#define _SRC_S21_SET_HPP_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "s21_tree.hpp"

namespace s21 {

template <typename K>
struct CompareSet {
  using key_type = K;
  key_type obj_;
  CompareSet(key_type obj) { obj_ = obj; };

  bool operator<(const K& a) const { return obj_ < a; }
  bool operator>(const K& a) const { return obj_ > a; }
  bool operator<=(const K& a) const { return obj_ <= a; }
  bool operator>=(const K& a) const { return obj_ >= a; }
  bool operator==(const K& a) const { return obj_ == a; }
  bool operator!=(const K& a) const { return obj_ != a; }
};

template <class K>
class set : public Tree<K, CompareSet<K>> {
 public:
  using key_type = K;
  using value_type = K;
  using reference = K&;
  using const_reference = const K&;
  using size_type = size_t;
  using node = TreeNode<K, CompareSet<K>>;
  using iterator = TreeIterator<K, CompareSet<K>>;
  using const_iterator = ConstTreeIterator<K, CompareSet<K>>;
  using set_compare = CompareSet<key_type>;
  using Tree<K, CompareSet<K>>::Tree;

  size_type max_size() const {
    std::allocator<key_type> alloc;
    return alloc.max_size() / 10;
  }

  iterator find(const key_type& key) const {
    node* tmp = this->findNode(key, this->root_);
    if (tmp) {
      iterator it = tmp;
      return (const_iterator)it;
    } else {
      return this->cend();
    }
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    return this->insertHelp(value);
  }

  bool contains(const key_type& key) const {
    node* res = findNode(key, this->root_);
    return (res) ? 1 : 0;
  }
};

}  // namespace s21

#endif  // _SRC_S21_SET_HPP_
