#ifndef _SRC_S21_MULTISET_HPP_
#define _SRC_S21_MULTISET_HPP_

#include "s21_set.hpp"
#include "s21_tree.hpp"

namespace s21 {

template <typename K>
struct CompareMulti {
  using key_type = K;
  key_type obj_;
  CompareMulti(key_type obj) { obj_ = obj; };

  bool operator<(const K& a) const { return obj_ < a; }
  bool operator>(const K& a) const { return obj_ > a; }
  bool operator<=(const K& a) const { return obj_ <= a; }
  bool operator>=(const K& a) const { return obj_ >= a; }
  bool operator==(const K& a) const { return obj_ == a; }
  bool operator!=(const K& a) const { return obj_ != a; }
};

template <class K>
class set;  //  зачем

template <class K>
class multiset : public Tree<K, CompareMulti<K>, true> {
 public:
  using key_type = K;
  using value_type = K; 
  using reference = K &;
  using const_reference = const K &;
  using size_type = size_t;
  using node = TreeNode<K, CompareMulti<K>>;
  using iterator = TreeIterator<K, CompareMulti<K>>;
  using const_iterator = TreeIterator<K, CompareMulti<K>, 1>;
  using Tree<K, CompareMulti<K>, true>::Tree;
  // using Tree<K, CompareMulti<K>, true>::insertHelp;

  iterator insert(const value_type& value) {
    return this->insertHelp(value).first;
  }

  iterator find(const key_type& key) {
    node* tmp = this->findNode(key, this->root_);
    if (tmp) {
      iterator it = tmp;
      return it;
    } else {
      return this->end();
    }
  }

  size_type max_size() const {
    std::allocator<key_type> alloc;
    return alloc.max_size() / 10;
  }
};

}  // namespace s21

#endif  // _SRC_S21_MULTISET_HPP_