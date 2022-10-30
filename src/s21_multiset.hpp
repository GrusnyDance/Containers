#ifndef _SRC_S21_MULTISET_HPP_
#define _SRC_S21_MULTISET_HPP_

#include "tree.h"

namespace s21 {

template <class K>
class multiset : public Tree<K, true> {
 public:
  using key_type = K;
  using value_type = K;
  using reference = K&;
  using const_reference = const K&;
  using size_type = size_t;
  using node = STree<K>*;
  using iterator = Iterator<K, true>;
  using Tree<K, true>::Tree;

  iterator insert(const value_type& value) {
    // code....
  }
};

}  // namespace s21

#endif  // _SRC_S21_MULTISET_HPP_