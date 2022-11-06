#ifndef _SRC_S21_MAP_HPP_
#define _SRC_S21_MAP_HPP_

#include <iostream>  // DEBUG
#include <limits>    // max_size
#include <string>
#include <type_traits>
#include <utility>  // initializer list, pair
#include <vector>

#include "s21_tree.hpp"

namespace s21 {

// принимает пару

template <typename Key, typename Value>
struct CompareMap {
  using myPair = std::pair<Key, Value>;
  myPair obj_;
  CompareMap(myPair obj) { obj_ = obj; };

  bool operator<(const myPair& a) const { return obj_.first < a.first; }
  bool operator>(const myPair& a) const { return obj_.first > a.first; }
  bool operator<=(const myPair& a) const { return obj_.first <= a.first; }
  bool operator>=(const myPair& a) const { return obj_.first >= a.first; }
  bool operator==(const myPair& a) const { return obj_.first == a.first; }
  bool operator!=(const myPair& a) const { return obj_.first != a.first; }
};

template <typename Key, typename Value>
class map : public Tree<std::pair<Key, Value>, CompareMap<Key, Value>> {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<key_type, mapped_type>;
  using node = TreeNode<value_type, CompareMap<Key, Value>>;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator<value_type, CompareMap<Key, Value>>;
  using const_iterator = ConstTreeIterator<value_type, CompareMap<Key, Value>>;
  using Tree<std::pair<Key, Value>, CompareMap<Key, Value>>::Tree;

  std::pair<iterator, bool> insert(const value_type& value) {
    return this->insertHelp(value);
  }

  // проверяет, существует ли ключ
  mapped_type& at(const key_type& key) const {
    value_type a = value_type(key, Value());
    node* res = this->findNode(a, this->root_);
    if (!res) {
      throw std::out_of_range("There is no such key");
    }
    return res->data_.second;
  }

  // присваивает если ключ не найден
  mapped_type& operator[](const key_type& key) {
    try {
      return at(key);
    } catch (...) {  // любое исключение
      value_type a = value_type(key, mapped_type());
      insert(a);
      return at(key);
    }
  }

  size_type max_size() const {  // it works i have no idea how
    return std::numeric_limits<size_type>::max() /
           (sizeof(value_type) + 3 * sizeof(node*) + 8 * sizeof(bool)) / 2;
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    std::pair<key_type, mapped_type> res(key, obj);
    return insert(res);
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    std::pair<key_type, mapped_type> value(key, obj);
    node* temp;
    if ((temp = this->findNode(value, this->root_)) != nullptr) {
      temp->data_.second = obj;
      iterator res(temp);
      return std::pair<iterator, bool>(res, false);
    } else {
      return this->insert(value);
    }
  }

  bool contains(const key_type& key) const {
    std::pair<key_type, value_type> a =
        std::pair<key_type, value_type>(key, value_type());
    node* res = this->findNode(a, this->root_);
    return (res) ? 1 : 0;
  }
};

}  // namespace s21

#endif  // _SRC_S21_MAP_HPP_