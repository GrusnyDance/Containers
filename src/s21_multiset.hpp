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
class multiset : public Tree<K, CompareMulti<K>, true> {
 public:
  using key_type = K;
  using value_type = K;
  using reference = K&;
  using const_reference = const K&;
  using size_type = size_t;
  using iterator = TreeIterator<K, CompareMulti<K>>;
  using const_iterator = ConstTreeIterator<K, CompareMulti<K>>;
  using Tree<K, CompareMulti<K>, true>::Tree;

 private:
  using node = TreeNode<K, CompareMulti<K>>;

 public:
  iterator insert(const value_type& value) {
    return this->insertHelp(value).first;
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

  size_type max_size() const {
    std::allocator<key_type> alloc;
    return alloc.max_size() / 10;
  }

  // returns the number of elements matching specific key
  size_type count(const key_type& key) const {
    size_type locCount = 0;
    iterator tmp;
    if ((tmp = find(key)) == this->cend()) {
      return 0;
    } else {
      locCount++;
      node* next = tmp.getPtr();
      while (next->left_ && next->data_ == next->left_->data_) {
        next = next->left_;
        locCount++;
      }
    }
    return locCount;
  }

  // returns range of elements matching a specific key
  std::pair<iterator, iterator> equal_range(const key_type& key) const {
    iterator lower = lower_bound(key);
    iterator upper = upper_bound(key);

    std::pair<iterator, iterator> a(lower, upper);
    return a;
  }

  // returns an iterator to the first element not less than the given key
  iterator lower_bound(const key_type& key) const {
    if (!this->size_) return this->cend();
    iterator res = this->cbegin();

    for (; (*res < key) && res != this->cend(); ++res) {
      ;
    }
    return res;
  }

  // returns an iterator to the first element greater than the given key
  iterator upper_bound(const key_type& key) const {
    iterator temp = lower_bound(key);
    if (temp == this->cend() || (temp.getPtr())->data_ > key) return temp;

    ++temp;
    if (temp.getPtr() == this->fakeNode) return this->cend();
    return temp;
  }
};

}  // namespace s21

#endif  // _SRC_S21_MULTISET_HPP_