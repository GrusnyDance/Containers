// maiamabl
/* dodelatb 
find()
end()*/

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

template<class Key>
struct STree {
  Key data_;
  STree<Key> *parent_;
  STree<Key> *left_;
  STree<Key> *right_;
  STree()
    : parent_(nullptr), left_(nullptr), right_(nullptr) {}
};

template<class K, bool MULTI>
class Iterator;

template<class K, bool MULTI>
class ConstIterator;

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
    using const_iterator = ConstIterator<K, MULTI>;

  private:
    STree<K> *first_; // min
    STree<K> *root_; // korenb
    STree<K> *fake_; // zaglushka
    size_type size_; // kol-vo elementov
    Compare comp_; // val1 < val2
  
  public:

    Tree() : first_(nullptr), root_(nullptr),
        size_(0), comp_(Compare()) {
        fake_ = new STree<K>();
    }

    Tree(std::initializer_list<key_type> const &keys) : first_(nullptr),
        root_(nullptr), size_(0), comp_(Compare()) {
      fake_ = new STree<K>();
      operator=(keys);
    }

    Tree(const Tree &other) {
        fake_ = new STree<K>();
        *this = other;
    }

    // I dont know, what the f**k =)
    Tree(Tree&& other) : first_(other.first_), root_(other.root_), size_(other.size_) {
      fake_ = new STree<K>();
      other.root_ = nullptr;
      other.first_ = nullptr;
      other.size_ = 0;
    }

    ~Tree() {
      delete fake_;
    }

    Tree& operator=(std::initializer_list<value_type> const& keys) {
      if (root_ != nullptr) {
        this->clear();
      }
      size_ = 0;
      root_ = nullptr;
      for (auto i : keys) {
        this->pasteNode(i);
      }
      maximum(root_);
      return *this;
    }
    
    void operator=(const Tree &other) {
      this->first_ = other.first_;
      this->fake_ = nullptr;
      this->root_ = other.root_;
      this->size_ = other.size_;
    }

    Tree& operator=(Tree&& other) {
      if (root_ == other.root_) {
        return *this;
      }
      if (root_ != nullptr) {
        this->clear();
      }
      root_ = other.root_;
      first_ = other.first_;
      size_ = other.size_;
      fake_ = nullptr;
      other.root_ = nullptr;
      other.first_ = nullptr;
      other.size_ = 0;
      return *this;
    }

    node getFirst() { return first_; }
    node getRoot() { return root_; }
    node getLast() { return fake_; }

    void clear() {
      this->size_ = 0;
      clearRecurs(root_);
      root_ = first_ = nullptr;
    }
    
    iterator begin() {
      iterator it(first_);
      return it;
    }

    const_iterator begin() const {
      const_iterator it(first_);
      return it;
    }

    iterator end() {
      // obrashenie = (sega)
      iterator it(fake_);
      return it;
    }

    const_iterator end() const {
      // obrashenie = (sega)
      const_iterator it(fake_);
      return it;
    }

    void erase(iterator pos) {
      if (root_ != nullptr || search(pos.ptr_->data_) != nullptr) {
        removeRecurs(this->root_, pos.ptr_->data_);
        size_--;
        // minimum(root_);
        // maximum(root_);
      }
    }

    void swap(Tree<K, MULTI> &other) {
      Tree<K, MULTI> temp = other;
      other = *this;
      *this = temp;
    }

    // ne robit
    void merge(Tree<K, MULTI> &other) {
      iterator it = other.begin();
      while (it != other.end()) {
        this->pasteNode(other.getFirst()->data_);
        it++;
      }
      other.clear();
    }

    bool empty() const {
      return size_ == 0 ? true : false;
    }

    size_type size() const {
      return size_;
    }

    size_type max_size() const {
      std::allocator<key_type> alloc;
      return alloc.max_size() / 10;
    }

    iterator find(const key_type &key) {
      if (search(key) != nullptr) {
        iterator it(search(key));
        return it;
      } else {
        // povedenie neopredeleno (sega)
        return end();
      }
    }

    bool contains(const key_type& key) const {
      return (search(key) ? true : false);
    }

    void printSorted(node root) {
      if (root != nullptr) {
        printSorted(root->left_);
        std::cout << root->data_  << " ";
        printSorted(root->right_);
      }
    }

  // help func
  protected:
    node minimum(node root) const {
      if (root == nullptr) {
        return root;
        
      }
      if (root->left_ == nullptr) {
        first_ = root;
        return root;
      }
      return minimum(root->left_);
    }

    node maximum(node root) const {
      if (root == nullptr) {
        return root;
      }
      if (root->right_ == nullptr) {
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
          return true;
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
      tmp->data_ = key;
      tmp->parent_ = nullptr;
      tmp->left_ = nullptr;
      tmp->right_ = nullptr;
      pasteNewNode(root_, tmp);
    }

    void pasteNewNode(node &root, node new_node) {
      node tmp_parent = root;
      node fake_parent = nullptr;

      while (tmp_parent != nullptr) {
        fake_parent = tmp_parent;
        if (comp_(new_node->data_, tmp_parent->data_)) { // new node < parent node
          tmp_parent = tmp_parent->left_; // move left
        } else {
          tmp_parent = tmp_parent->right_; // move right
        }
      }
      new_node->parent_ = fake_parent;
      if (new_node->parent_ != nullptr) {
        if (new_node->data_ < fake_parent->data_) {
          fake_parent->left_ = new_node; // insert new node left
        } else {
          fake_parent->right_ = new_node; // insert new node right
        }
      } else {
        root_ = new_node; // new node == head tree
      }
    }

    node search(const key_type key) const {
      return searchRecurs(root_, key);
    }

    node searchRecurs(node root, value_type key) const {
      if (root == nullptr) {
        return nullptr;
      }
      if (root->data_ == key) {
        return root;
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

    reference operator*() const {
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

    node getPtr() const { return this->ptr_; }
};

template<class K, bool MULTI>
class ConstIterator {
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
    ConstIterator() : ptr_(nullptr) {}
    
    ConstIterator(node ptr) : ptr_(ptr){}
    
    ConstIterator(const ConstIterator &other) : ptr_(other.ptr_) {}

    ~ConstIterator() {}

    node* operator->() const { return ptr_; }
    
    const_reference operator*() const {
      return ptr_->data_;
    }

    bool operator!=(const ConstIterator &other) {
      return this->ptr_ != other.ptr_;
    }

    bool operator==(const ConstIterator &other) {
      return this->ptr_ == other.ptr_;
    }

    ConstIterator& operator=(const ConstIterator other) {
        this->ptr_ = other.ptr_;
        return *this;
    }

    ConstIterator &operator++() {
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

    ConstIterator &operator--() {
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

    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ConstIterator operator--(int) {
      ConstIterator tmp = *this;
      --(*this);
      return tmp;
    }

    node getPtr() const { return this->ptr_; }
};

} // namespase s21

#endif  // __SRC_BTREE_H__
