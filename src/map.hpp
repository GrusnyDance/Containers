#pragma once

#include <iostream>  // DEBUG
#include <limits>    // max_size
#include <string>
#include <type_traits>
#include <utility>  // initializer list, pair

namespace s21 {
// принимает пару, узел дерева
template <typename Data>
class TreeNode {
 public:
  Data data_;
  TreeNode* left_;
  TreeNode* right_;
  TreeNode* parent_;

  TreeNode() { left_ = right_ = parent_ = nullptr; }
  explicit TreeNode(Data data, TreeNode* parent = NULL, TreeNode* left = NULL,
                    TreeNode* right = NULL);

  TreeNode(const TreeNode& other) { *this = other; }
  TreeNode(TreeNode&& other) = default;
  TreeNode& operator=(const TreeNode& other);
  ~TreeNode() {}

  TreeNode* nextNode();
  TreeNode* previousNode();
  TreeNode* getMin();
};

// принимает пару, итератор
template <typename Data, bool isConst = 0>
class TreeIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;  // хз зачем
  using node_pointer = TreeNode<Data>*;
  using value_type = Data;

  friend class TreeNode<Data>;
  node_pointer ptr_;

  TreeIterator() { ptr_ = nullptr; };
  TreeIterator(node_pointer ptr) { ptr_ = ptr; };
  TreeIterator(const TreeIterator& other) { *this = other; }
  ~TreeIterator() {}

  TreeIterator& operator=(const TreeIterator& other);
  TreeIterator operator++(int);
  TreeIterator operator--(int);
  TreeIterator& operator++();
  TreeIterator& operator--();

  node_pointer getPtr() { return ptr_; };
  node_pointer operator->() { return (ptr_); }
  value_type operator*() { return (ptr_->data_); }
  bool operator==(const TreeIterator& other);
  bool operator!=(const TreeIterator& other);
};

template <typename Key, typename Value>
struct Compare {  // структура для сравнения узлов
  using myPair = std::pair<Key, Value>;
  myPair obj_;
  Compare(myPair obj) { obj_ = obj; };

  bool operator<(const myPair& a) const { return obj_.first < a.first; }
  bool operator>(const myPair& a) const { return obj_.first > a.first; }
  bool operator<=(const myPair& a) const { return obj_.first <= a.first; }
  bool operator>=(const myPair& a) const { return obj_.first >= a.first; }
  bool operator==(const myPair& a) const { return obj_.first == a.first; }
  bool operator!=(const myPair& a) const { return obj_.first != a.first; }
};

template <typename Key, typename Value>
class Map {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<key_type, mapped_type>;
  using node = TreeNode<value_type>;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator<value_type>;
  using const_iterator = TreeIterator<value_type, 1>;
  using map_compare = Compare<key_type, mapped_type>;  // для сравнения узлов

 private:
  friend class TreeNode<value_type>;
  friend class TreeIterator<value_type>;
  node* root_;
  node* fakeNode;  // нода, на которую будет указывать end
  size_type size_ = 0;

 public:
  Map();
  Map(std::initializer_list<key_type> const& items);
  Map(const Map& other);
  Map(Map&& other);
  ~Map();

  void clear();
  void operator=(Map&& other);
  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);
  iterator begin();
  iterator end();
  //   const_iterator begin();
  //   const_iterator end();

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }  // ok
  size_type max_size() const;
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);

  void erase(iterator pos);
  void swap(Map& other);
  void merge(Map& other);
  bool contains(const key_type& key);

 protected:
  void copyRecursive(node* root, node* root_fake, node* other,
                     node* other_fake);
  void clearRecursive(node* root);
  node* findNode(const key_type& key, node* root);
  void insertRecursive(node* root, node* parent, node* val, bool right);
  void insertForMerge(node* val);

  void deleteBothChildren(iterator pos);
  void deleteNoLeftChildren(iterator pos);
  void deleteNoRightChildren(iterator pos);
  void deleteNoChildren(iterator pos);
};
}  // namespace s21

#include "iterator.inl"
#include "map.inl"
#include "node.inl"