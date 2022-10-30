#ifndef _SRC_S21_SET_HPP_
#define _SRC_S21_SET_HPP_

#include "tree.h"

namespace s21 {

template<class K>
class set : public Tree<K, false> {
  public:  
    using key_type = K;
    using value_type = K;
    using reference = K&;
    using const_reference = const K&;
    using size_type = size_t;
    using node = STree<K>*;
    using iterator = Iterator<K, false>;
    using Tree<K, false>::Tree;

    std::pair<iterator, bool> insert(const value_type &value) {
      std::pair<iterator, bool> result;
      if (this->pasteNode(value)) {
        result = std::pair<iterator, bool>(this->find(value), true);
      } else {
        result = std::pair<iterator, bool>(this->find(value), false);
      }
      this->maximum(this->getRoot());
      return result;
    }
};

}

#endif  // _SRC_S21_SET_HPP_
