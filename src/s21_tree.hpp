

#ifndef _SRC_TREE_H_
#define _SRC_TREE_H_

#include <iostream>  // DEBUG
#include <limits>    // max_size
#include <string>
#include <utility>  // initializer list, pair
#include <vector>

namespace s21 {
template <typename Data, class Compare>
class TreeNode {
 public:
  Data data_;
  TreeNode* left_;
  TreeNode* right_;
  TreeNode* parent_;
  using common_compare = Compare;

  // конструктор без параметров
  TreeNode() { left_ = right_ = parent_ = nullptr; }
  // конструктор с параметрами
  explicit TreeNode(Data data, TreeNode* parent = NULL, TreeNode* left = NULL,
                    TreeNode* right = NULL) {
    data_ = data;
    parent_ = parent;
    left_ = left;
    right_ = right;
  }

  // конструктор копирования
  TreeNode(const TreeNode& other) { *this = other; }
  // конструктор перемещения, нет динамической памяти
  TreeNode(TreeNode&& other) = default;
  // оператор присваивания копированием
  TreeNode& operator=(const TreeNode& other) {
    if (this != &other) {
      data_ = other.data_;
      parent_ = other.parent_;
      left_ = other.left_;
      right_ = other.right_;
    }
    return *this;
  }
  ~TreeNode() {}

  // функции для поиска предыдущего и следующего узла, чтобы итерироваться в обе
  // стороны
  TreeNode* nextNode() {  // ищет следующий по значению узел
    TreeNode* temp = this;
    if (temp->right_) {
      temp = temp->right_;
      while (temp->left_) temp = temp->left_;
    } else if (temp->parent_) {
      if (common_compare(temp->data_) == temp->parent_->data_) {
        return temp->parent_;
      }
      // если значение крайнее правое в левой ветке, следующее по величине
      // значение - корень
      while (temp->parent_ && temp->parent_->right_ == temp) {
        // доходим до первого уровня левой ветки (если узел в правой ветке, в
        // цикл не заходим)
        temp = temp->parent_;
      }
      temp = temp->parent_;  // поднимаемся на уровень вверх
    }
    return temp;
  }

  TreeNode* previousNode() {
    TreeNode* temp = this;
    if (temp->left_) {
      temp = temp->left_;
      while (temp->right_) temp = temp->right_;
    } else if (temp->parent_) {
      // если значение крайнее левое в правой ветке
      while (temp->parent_ && (temp->parent_->left_ == temp)) {
        temp = temp->parent_;
      }
      temp = temp->parent_;
    }
    return temp;
  }

  TreeNode* getMin() {
    TreeNode* temp = this;
    while (temp->left_) {
      temp = temp->left_;
    }
    return temp;
  }

  TreeNode* getMax() {
    TreeNode* temp = this;
    while (temp->right_) {
      temp = temp->right_;
    }
    return temp;
  }
};

template <typename Data, class Compare>
class ConstTreeIterator;

template <typename Data, class Compare>
class TreeIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;  // хз зачем
  using value_type = Data;
  using node_pointer = TreeNode<Data, Compare>*;

  node_pointer ptr_;
  // дружественный класс ноды
  friend class TreeNode<Data, Compare>;
  friend class ConstTreeIterator<Data, Compare>;

  TreeIterator() { ptr_ = nullptr; };
  TreeIterator(node_pointer ptr) { ptr_ = ptr; };
  TreeIterator(const TreeIterator& other) { *this = other; }
  TreeIterator(const ConstTreeIterator<Data, Compare>& other) { *this = other; }
  ~TreeIterator() {}

  TreeIterator& operator=(const TreeIterator& other) {
    ptr_ = other.ptr_;
    return *this;
  }

  TreeIterator& operator=(const ConstTreeIterator<Data, Compare>& other) {
    ptr_ = other.ptr_;
    return *this;
  }

  TreeIterator operator++(int) {
    TreeIterator before(*this);
    ++(*this);
    return before;
  }

  TreeIterator operator--(int) {
    TreeIterator before(*this);
    --(*this);
    return before;
  }

  TreeIterator& operator++() {
    ptr_ = ptr_->nextNode();
    return *this;
  }

  TreeIterator& operator--() {
    ptr_ = ptr_->previousNode();
    return *this;
  }

  node_pointer getPtr() { return ptr_; };
  node_pointer operator->() { return (ptr_); }
  value_type operator*() { return (ptr_->data_); }
  bool operator==(const TreeIterator& other) { return (ptr_ == other.ptr_); }
  bool operator!=(const TreeIterator& other) { return (ptr_ != other.ptr_); }
};

template <typename Data, class Compare>
class ConstTreeIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;  // хз зачем
  using value_type = const Data;
  using node_pointer = TreeNode<Data, Compare>*;
  friend class TreeIterator<Data, Compare>;

  node_pointer ptr_;
  // дружественный класс ноды
  friend class TreeNode<Data, Compare>;

  ConstTreeIterator() { ptr_ = nullptr; };
  ConstTreeIterator(node_pointer ptr) { ptr_ = ptr; };
  ConstTreeIterator(const TreeIterator<Data, Compare>& other) { *this = other; }
  ConstTreeIterator(const ConstTreeIterator& other) { *this = other; }
  ~ConstTreeIterator() {}

  ConstTreeIterator& operator=(const ConstTreeIterator& other) {
    ptr_ = other.ptr_;
    return *this;
  }

  ConstTreeIterator& operator=(const TreeIterator<Data, Compare>& other) {
    ptr_ = other.ptr_;
    return *this;
  }

  ConstTreeIterator operator++(int) {
    ConstTreeIterator before(*this);
    ++(*this);
    return before;
  }

  ConstTreeIterator operator--(int) {
    ConstTreeIterator before(*this);
    --(*this);
    return before;
  }

  ConstTreeIterator& operator++() {
    // std::cout << "size is " << ptr_->data_ << std::endl;
    ptr_ = ptr_->nextNode();
    return *this;
  }

  ConstTreeIterator& operator--() {
    ptr_ = ptr_->previousNode();
    return *this;
  }

  node_pointer getPtr() { return ptr_; };
  node_pointer operator->() { return (ptr_); }
  const value_type& operator*() { return (ptr_->data_); }
  bool operator==(const ConstTreeIterator& other) {
    return (ptr_ == other.ptr_);
  }
  bool operator!=(const ConstTreeIterator& other) {
    return (ptr_ != other.ptr_);
  }
};

template <typename Data, class Compare, bool Multi = false>
class Tree {
 public:
  using value_type = Data;
  using node = TreeNode<value_type, Compare>;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator<value_type, Compare>;
  using const_iterator = ConstTreeIterator<value_type, Compare>;
  using common_compare = Compare;

 protected:
  node* root_;
  node* fakeNode;  // нода, на которую будет указывать end
  size_type size_ = 0;
  friend class TreeNode<value_type, Compare>;
  friend class TreeIterator<value_type, Compare>;

 public:
  Tree() {
    fakeNode = (node*)new node();  // скобки для вызова дефолтного конструктора
    root_ = (node*)new node();
    root_->right_ = fakeNode;
    fakeNode->parent_ = root_;
  }

  // инициализация листом
  Tree(std::initializer_list<value_type> const& items) : Tree() {
    for (auto iter = items.begin(); iter != items.end(); ++iter)
      insertHelp(*iter);
  }

  Tree(const Tree& other) : Tree() {  // копирование
    if (other.size_ > 0) {
      copyRecursive(root_, fakeNode, other.root_, other.fakeNode);
      size_ = other.size_;
    }
  }

  Tree(Tree&& other) : Tree() {  // перемещение
    delete fakeNode;
    delete root_;
    root_ = other.root_;
    size_ = other.size_;
    fakeNode = other.fakeNode;
    other.root_ = nullptr;
    other.fakeNode = nullptr;
    other.size_ = 0;
  }

  ~Tree() {  // деструктор
    clear();
    if (fakeNode) delete fakeNode;
    if (root_) delete root_;
  }

  void clear() {
    if (root_ == nullptr) return;
    if (size_ > 0) {
      clearRecursive(root_);
      root_->right_ = fakeNode;
      fakeNode->parent_ = root_;
      size_ = 0;
    }
  }

  void operator=(Tree& other) {
    this->clear();
    for (auto i = other.begin(); i != other.end(); ++i) {
      this->insertHelp(*i);
    }
  }

  // оператор присваивания перемещением
  void operator=(Tree&& other) {
    if (this == &other) return;
    clear();
    delete root_;
    delete fakeNode;

    root_ = other.root_;
    size_ = other.size_;
    fakeNode = other.fakeNode;
    other.root_ = other.fakeNode = nullptr;
    other.size_ = 0;
  }

  iterator begin() {
    node* temp = root_->getMin();
    iterator result(temp);
    return result;
  }
  iterator end() {
    iterator result(fakeNode);
    return result;
  }
  const_iterator cbegin() const {
    node* temp = root_->getMin();
    const_iterator result(temp);
    return result;
  }
  const_iterator cend() const {
    const_iterator result(fakeNode);
    return result;
  }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }  // ok

  // bool показывает произошла ли вставка
  std::pair<iterator, bool> insertHelp(const value_type& value) {
    // std::cout << value << std::endl;
    if (empty()) {
      root_->data_ = value;
      ++size_;
      iterator res(root_);
      return std::pair<iterator, bool>(res, true);
    } else {
      node* temp;
      if (!Multi) {  // 1 yes, 0 no
        if ((temp = findNode(value, root_)) !=
            nullptr) {  // TBD два раза проходится по дереву если insert or
                        // assign
          iterator res(temp);
          return std::pair<iterator, bool>(res, false);
        }
      }
      temp = new node(value);
      insertRecursive(root_, 0, temp, 0);
      ++size_;
      iterator res(temp);
      return std::pair<iterator, bool>(res, true);
    }
  }

  void erase(iterator pos) {  // 4 сценария
    // нет детей
    if (!pos->left_ && (!pos->right_ || pos->right_ == fakeNode)) {
      deleteNoChildren(pos);
    } else if (!pos->right_ || pos->right_ == fakeNode) {
      deleteNoRightChildren(pos);
    } else if (!pos->left_) {
      deleteNoLeftChildren(pos);
    } else {
      deleteBothChildren(pos);
    }
    --size_;
  }

  void swap(Tree& other) {
    Tree temp = std::move(other);
    other = std::move(*this);
    *this = std::move(temp);
  }

  void merge(Tree& other) {
    for (auto it = other.begin(); it != other.end(); it++) {
      insertForMerge(it.getPtr());
    }
    other.clear();
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    std::vector<std::pair<iterator, bool>> res = {(insertHelp(args))...};
    return res;
  }

 protected:
  void copyRecursive(node* root, node* root_fake, node* other,
                     node* other_fake) {
    root->data_ = other->data_;
    if (other->left_ != nullptr) {
      node* temp = new node();
      temp->parent_ = root;
      root->left_ = temp;
      copyRecursive(temp, root_fake, other->left_, other_fake);
    }
    if (other->right_ != nullptr) {
      if (other->right_ == other_fake) {
        root->right_ = root_fake;
        root_fake->parent_ = root;
      } else {
        node* temp = new node();
        temp->parent_ = root;
        root->right_ = temp;
        copyRecursive(temp, root_fake, other->right_, other_fake);
      }
    }
  }

  void clearRecursive(node* root) {
    if (root) {
      if (root->left_) clearRecursive(root->left_);
      if (root->right_) clearRecursive(root->right_);
      if (root != root_ && root != fakeNode && root) {
        delete root;
        root = nullptr;
      }
    }
  }

  node* findNode(const value_type& key, node* root) const {
    if (size_ == 0 || root == 0 || root == fakeNode) {
      return nullptr;
    }
    if (common_compare(key) == root->data_) {
      return root;
    }
    return (common_compare(root->data_) > key) ? findNode(key, root->left_)
                                               : findNode(key, root->right_);
  }

  void insertRecursive(node* root, node* parent, node* val, bool right) {
    if (!root || root == fakeNode) {
      if (root == fakeNode) {
        parent->right_ = fakeNode->parent_ = val;
        val->right_ = fakeNode;
        val->parent_ = parent;
      } else {
        val->parent_ = parent;
        if (right) {
          parent->right_ = val;
        } else {
          parent->left_ = val;
        }
      }
    } else if (common_compare(val->data_) == root->data_) {
      if (root->left_) {
        root->left_->parent_ = val;
        val->parent_ = root;
        val->left_ = root->left_;
        root->left_ = val;
      } else {
        root->left_ = val;
        val->parent_ = root;
      }
    } else if (common_compare(val->data_) > root->data_) {
      insertRecursive(root->right_, root, val, 1);
    } else if (common_compare(val->data_) < root->data_) {
      insertRecursive(root->left_, root, val, 0);
    }
  }

  void deleteBothChildren(iterator pos) {
    node* minRight = pos->right_->getMin();
    value_type val = minRight->data_;
    iterator recursive(minRight);
    erase(recursive);
    ++size_;
    pos->data_ = val;
  }

  void deleteNoLeftChildren(iterator pos) {
    if (pos.getPtr() == root_) {
      root_ = pos->right_;
      root_->parent_ = nullptr;
      delete pos.getPtr();
    } else {
      iterator parent = pos->parent_;
      if (common_compare(*pos) > parent->data_) {  // если pos правый узел
        parent->right_ = pos->right_;
      } else {
        parent->left_ = pos->right_;
      }
      pos->right_->parent_ = parent.getPtr();
      delete pos.getPtr();
    }
  }

  void deleteNoRightChildren(iterator pos) {
    if (pos.getPtr() == root_) {
      iterator newRoot = pos->left_;
      node* temp = pos->left_->getMax();
      iterator newMax(temp);

      newMax->right_ = fakeNode;
      fakeNode->parent_ = newMax.getPtr();
      root_ = newRoot.getPtr();
      newRoot->parent_ = nullptr;
      delete pos.getPtr();
    } else {
      iterator newPos = pos->left_;
      iterator parent = pos->parent_;
      if (common_compare(*pos) > parent->data_) {  // правый узел
        if (pos->right_ == fakeNode) {
          parent->right_ = newPos.getPtr();
          newPos->parent_ = parent.getPtr();

          node* temp = pos->left_->getMax();
          iterator newMax(temp);
          fakeNode->parent_ = newMax.getPtr();
          temp->right_ = fakeNode;
        } else {
          parent->right_ = newPos.getPtr();
          newPos->parent_ = parent.getPtr();
        }
      } else {  // левый узел, тут не может быть фейковой ноды
        parent->left_ = newPos.getPtr();
        newPos->parent_ = parent.getPtr();
      }
      delete pos.getPtr();
    }
  }

  void deleteNoChildren(iterator pos) {
    if (!size_) {
      ++size_;
      return;
    } else if (pos.getPtr() == root_) {
      size_ = 1;
    } else if (pos->right_ == fakeNode) {
      fakeNode->parent_ = pos->parent_;
      pos->parent_->right_ = fakeNode;
      delete pos.getPtr();
    } else {
      if (common_compare(*pos) > pos->parent_->data_) {
        pos->parent_->right_ = nullptr;
      } else {
        pos->parent_->left_ = nullptr;
      }
      delete pos.getPtr();
    }
  }

  void insertForMerge(node* val) {
    value_type value = val->data_;

    if (empty()) {
      root_->data_ = value;
      ++size_;
    } else {
      node* temp;
      // если узел с таким ключом уже есть
      if (!Multi) {
        if ((temp = findNode(value, root_)) != nullptr) {
          return;
        }
      }
      temp = new node(value);
      insertRecursive(root_, 0, temp, 0);
      ++size_;
    }
  }
};

}  // namespace s21

#endif  // _SRC_TREE_H_
