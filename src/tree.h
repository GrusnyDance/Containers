// maiamabl
/* dodelatb 
find()
eraze() or remove() sega kogda odin key */

#ifndef __SRC_BTREE_H__
#define __SRC_BTREE_H__

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace s21 {

enum eColor {
  RED,
  BLACK
};

template<class Key>
struct STree {
  Key data_;
  eColor color_;
  STree<Key> *parent_;
  STree<Key> *left_;
  STree<Key> *right_;
  STree()
    : color_(BLACK), parent_(nullptr), left_(nullptr), right_(nullptr) {}
};

template<class K, bool MULTI>
class Iterator;

template<class K, bool MULTI, class Compare = std::less<K>>
class Tree {  
  public:
    using key_type = K;
    using value_type = K;
    using reference = K&;
    using const_reference = const K&;
    using size_type = size_t;
    using node = STree<K>*;
    using compare = Compare;
    using iterator = Iterator<K, MULTI>;

  private:
    STree<K> *first_;
    STree<K> *root_;
    STree<K> *last_;
    size_type size_;
    Compare comp_;
  
  public:

    Tree() {
      this->first_ = nullptr;
      this->root_ = nullptr;
      this->last_ = nullptr;
      this->size_ = 0;
      this->comp_ = Compare();
    }

    Tree(std::initializer_list<key_type> const &keys) {
      operator=(keys);
    }

    Tree(const Tree &other) {
      this->first_ = other.first_;
      this->last_ = other.last_;
      this->root_ = other.root_;
      this->size_ = other.size_;
    }

    Tree(Tree&& other)
      : root_(other.root_), first_(other.first_), size_(other.size_) {
      last_ = nullptr;
      other.root_ = nullptr;
      other.front_ = nullptr;
      other.size_ = 0;
    }
        
    ~Tree() {}

    Tree& operator=(std::initializer_list<value_type> const& keys) {
      if (root_ != nullptr) {
        this->clear();
      }
      size_ = 0;
      root_ = nullptr;
      for (auto i : keys) {
        this->pasteNode(i);
      }
      minimum(root_);
      maximum(root_);
      return *this;
    }
    
    void operator=(const Tree &other) {
      this->first_ = other.first_;
      this->last_ = other.last_;
      this->root_ = other.root_;
      this->size_ = other.size_;
      // return *this;
    }

    node getFirst() { return first_; }
    node getRoot() { return root_; }
    node getLast() { return last_; }

    void clear() {
      this->size_ = 0;
      clearRecurs(root_);
      root_ = first_ = last_ = nullptr;
    }

    std::pair<iterator, bool> insert(const value_type &value) {
      std::pair<iterator, bool> result;
      if (pasteNode(value)) {
        result = std::pair<iterator, bool>(find(value), true);
      } else {
        result = std::pair<iterator, bool>(find(value), false);
      }
      minimum(root_);
      maximum(root_);
      return result;
    }

    iterator find(const key_type &key) {
      if (search(key) != nullptr) {
        iterator it(search(key));
        return it;
      } else {
        return nullptr;
      }
    }
    
    iterator begin() {
      iterator it(first_);
      return it;
    }

    iterator begin() const {
      iterator it(first_);
      return it;
    }

    iterator end() {
      iterator it(last_);
      return it;
    }

    iterator end() const {
      iterator it(last_);
      return it;
    }

    bool erase(const key_type key) {
      bool result = false;
      if (root_ == nullptr || search(key) == nullptr) {
        return false;
      } else {
        removeRecurs(this->root_, key);
        size_--;
        // result = true;
        return true;
      }
      minimum(root_);
      maximum(root_);
      return result;
    }

    void swap(node & other) {
      Tree<K, MULTI> temp = other;
      other = *this;
      *this = temp;
    }

    void merge(node& other) {
      iterator it = other.begin();
      while (it != other.end()) {
        this->insert(*it);
        it++;
      }
      other.clear();
    }

    bool contains(const key_type& key) {
      int res = 0;
      if (search(key)) {
        res = 1;
      }
      return res;
    }

    bool empty() const {
      return root_ == nullptr ? true : false;
    }

    size_type size() const {
      return size_;
    }

    size_type max_size() const {
      std::allocator<key_type> alloc;
      return alloc.max_size() / 10;
    }

    void printSorted(node root) {
      if (root != nullptr) {
        printSorted(root->left_);
        std::cout << root->data_  << " ";
        printSorted(root->right_);
      }
    }

  // help func
  private:

    node minimum(node root) {
      if (root == nullptr) {
        return root;
        
      }
      if (root->left_ == nullptr) {
        first_ = root;
        return root;
      }
      return minimum(root->left_);
    }

    node maximum(node root) {
      if (root == nullptr) {
        return root;
      }
      if (root->right_ == nullptr) {
        last_ = root;
        return root;
      }
      return maximum(root->right_);
    }

    bool pasteNode(key_type key) {
      bool result = false;
      if (MULTI == false) { // if mode = no duplicate
        if (search(key) == nullptr) {
          initNewNode(key);
          size_++;
          result = true;
        }
      } else {
        initNewNode(key);
        size_++;
        result = true;
      }
      return result;
    }

    void initNewNode(key_type key) {
      node tmp = new STree<key_type>;
      tmp->color_ = RED;
      tmp->data_ = key;
      tmp->parent_ = nullptr;
      tmp->left_ = nullptr;
      tmp->right_ = nullptr;
      pasteNewNode(root_, tmp);
    }

    void pasteNewNode(node &root, node new_node) {
      node tmp_parent = root;
      node last_parent = nullptr;

      while (tmp_parent != nullptr) {
        last_parent = tmp_parent;
        if (comp_(new_node->data_, tmp_parent->data_)) { // new node < parent node
          tmp_parent = tmp_parent->left_; // move left
        } else {
          tmp_parent = tmp_parent->right_; // move right
        }
      }
      new_node->parent_ = last_parent;
      if (new_node->parent_ != nullptr) {
        if (new_node->data_ < last_parent->data_) {
          last_parent->left_ = new_node; // insert new node left
        } else {
          last_parent->right_ = new_node; // insert new node right
        }
      } else {
        root_ = new_node; // new node == head tree
      }
    }

    node search(const key_type key) const {
      return searchRecurs(root_, key);
    }

    node searchRecurs(node root, value_type key) const {
      node result = root;
      if (root == nullptr || root->data_ == key) {
        return result;
      }
      if (comp_(root->data_, key)) {
        return searchRecurs(root->right_, key);
      } else {
        return searchRecurs(root->left_, key);
      }
    }

    node removeRecurs(node &root, key_type key) {
      if (root != nullptr) {
        if (key < root->data_) {
          root->left_ = removeRecurs(root->left_, key);
        } else if (key > root->data_) {
          root->right_ = removeRecurs(root->right_, key);
        } else if (root->left_ != nullptr && root->right_ != nullptr) {
          root->data_ = minimum(root->right_)->data_;
          root->right_ = removeRecurs(root->right_, root->data_);
        } else {
          node tmp = root;
          if (root->left_ != nullptr) {
            root = root->left_;
          } else if (root->right_ != nullptr) {
            root = root->right_;
          } else {
            root = nullptr;
          }
          delete tmp;
        }
      }
      return root;
    }

    void clearRecurs(node root) {
      if (root == nullptr) {
        return;
      }
      if (root->left_ != nullptr) {
        clearRecurs(root->left_);
      }
      if (root->right_ != nullptr) {
        clearRecurs(root->right_);
      }
      delete root;
    }

};

template<class K, bool MULTI>
class Iterator {
  public:
    using key_type = K;
    using value_type = K;
    using reference = K&;
    using const_reference = const K&;
    using size_type = size_t;
    using node = STree<K>*;
    friend class Tree<K, MULTI>;

  protected:
    node ptr_;

  public:
  
    Iterator() : ptr_(nullptr) {}
    
    Iterator(node ptr) : ptr_(ptr){}
    
    Iterator(const Iterator &other) : ptr_(other.ptr_) {}

    ~Iterator() {}

    node* operator->() const { return ptr_; }

    const_reference operator*() const {
      return ptr_->data_;
    }

    bool operator!=(const Iterator &other) {
      return this->ptr_ != other.ptr_;
    }

    bool operator==(const Iterator &other) {
      return this->ptr_ == other.ptr_;
    }

    Iterator& operator=(const Iterator other) {
        this->ptr_ = other.ptr_;
        return *this;
    }

    Iterator &operator++() {
      if (ptr_->right_ != nullptr) {
        ptr_ = ptr_->right_;
        while (ptr_->left_ != nullptr) {
          ptr_ = ptr_->left_;
        }
      } else {
        node temp = ptr_->parent_;
        while (ptr_ == temp->right_ && temp->parent_ != nullptr) {
          ptr_ = temp;
          temp = temp->parent_;
        }
        if (ptr_ == temp->left_) {
          ptr_ = temp;
        } else {
          ptr_ = nullptr;
        }
      }
    return *this;
    }

  Iterator &operator--() {
      if (ptr_->left_ != nullptr) {
      ptr_ = ptr_->left_;
      while (ptr_->right_ != nullptr) {
        ptr_ = ptr_->right_;
      }
    } else {
      node temp = ptr_->parent_;
      while (ptr_ == temp->left_ && temp->parent_ != nullptr) {
        ptr_ = temp;
        temp = temp->parent_;
      }
      if (ptr_ == temp->right_) {
        ptr_ = temp;
      } else {
        ptr_ = nullptr;
      }
    }
    return *this;
  }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }

    node getPtr() { return this->ptr_; }
};

} // namespase s21

#endif  // __SRC_BTREE_H__
