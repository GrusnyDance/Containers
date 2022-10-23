#include <iostream>  // DEBUG
#include <limits>    // max_size
#include <string>
#include <type_traits>
#include <utility>  // initializer list, pair

namespace s21 {
// принимает пару
template <typename Data>
class TreeNode {
 protected:
  Data data_;
  TreeNode* left_;
  TreeNode* right_;
  TreeNode* parent_;

 public:
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
};

// принимает пару
template <typename Data, bool isConst = 0>
class TreeIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;  // хз зачем
  using node_pointer = TreeNode<Data>*;
  using value_type = Data;

 protected:
  node_pointer ptr_;
  // дружественный класс ноды
  friend class TreeNode<Data>;

 public:
  TreeIterator() { ptr_ = nullptr; };
  TreeIterator(node_pointer ptr) { ptr_ = ptr; };
  TreeIterator(const TreeIterator& other) { *this = other; }
  ~TreeIterator() {}

  TreeIterator& operator=(const TreeIterator& other) {
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

template <typename Key, typename Value>
struct Compare {
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

 protected:
  using map_compare =
      Compare<key_type, mapped_type>;  // как функтор для сравнения пар

  node* root_;
  node* fakeNode;  // нода, на которую будет указывать end
  size_type size_ = 0;
  friend class TreeNode<value_type>;
  friend class TreeIterator<value_type>;

 public:
  Map() {
    fakeNode = new node();  // скобки для вызова дефолтного конструктора
    root_ = new node();
    root_->right_ = fakeNode;
    fakeNode->parent_ = root_;
  }

  // инициализация листом
  Map(std::initializer_list<key_type> const& items) : Map() {
    for (auto iter = items.begin(); iter != items.end(); ++iter) insert(*iter);
  }

  Map(const Map& other) : Map() {  // копирование
    if (other.size_ > 0) {
      copyRecursive(root_, fakeNode, other.root_, other.fakeNode);
      size_ = other.size_;
    }
  }

  Map(Map&& other) : Map() {  // перемещение
    delete fakeNode;
    delete root_;
    root_ = other.root_;
    size_ = other.size_;
    fakeNode = other.fakeNode;
    other.root_ = nullptr;
    other.fakeNode = nullptr;
    other.size_ = 0;
  }

  ~Map() {  // деструктор
    clear();
  }

  void clear() {
    if (size_ > 0) {
      clearRecursive(root_);
      root_ = fakeNode = nullptr;
      size_ = 0;
    }
    if (fakeNode) delete fakeNode;
    if (root_) delete root_;
  }

  // оператор присваивания перемещением
  void operator=(Map&& other) {
    if (this == &other) return;
    clearRecursive(root_);

    root_ = other.root_;
    size_ = other.size_;
    fakeNode = other.fakeNode;
    other.root_ = other.fakeNode = nullptr;
    other.size_ = 0;
  }

  // проверяет, существует ли ключ
  mapped_type& at(const key_type& key) {
    node* res = findNode(
        key,
        root_);  // не сработает без передачи вызывающего объекта тк рекурсия?
    if (!res) {
      throw std::out_of_range("There is no such key");
    }
    return res->data_.second;
  }

  // присваивает если ключ не найден
  mapped_type& operator[](const key_type& key) {
    try {
      return at(key);
    } catch (...) {   // любое исключение
      mapped_type a;  // обман компилятора:<>
      if (std::is_same_v<mapped_type, std::string>) {
        insert(value_type(key, a));
      } else {
        insert(value_type(key, 0));
      }
      return at(key);
    }
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
  const_iterator begin() const {
    node* temp = root_->getMin();
    const_iterator result(temp);
    return result;
  }
  const_iterator end() const {
    const_iterator result(fakeNode);
    return result;
  }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }  // ok
  size_type max_size() const {              // it works i have no idea how
    return std::numeric_limits<size_type>::max() /
           (sizeof(value_type) + 3 * sizeof(node*) + 8 * sizeof(bool)) / 2;
  }

  // bool показывает произошла ли вставка
  std::pair<iterator, bool> insert(const value_type& value) {
    if (empty()) {
      root_->data_ = value;
      ++size_;
      iterator res(root_);
      return std::pair<iterator, bool>(res, true);
    } else {
      node* temp;
      if ((temp = findNode(value.first, root_)) !=
          nullptr) {  // TBD два раза проходится по дереву если insert or assign
        iterator res(temp);
        return std::pair<iterator, bool>(res, false);
      }
      temp = new node(value);
      insertRecursive(root_, 0, temp, 0);
      ++size_;
      iterator res(temp);
      return std::pair<iterator, bool>(res, true);
    }
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
    if ((temp = findNode(value.first, root_)) != nullptr) {
      temp->data_.second = obj;
      iterator res(temp);
      return std::pair<iterator, bool>(res, false);
    } else {
      return insert(value);
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

  void swap(Map& other) {
    Map temp = other;
    other = *this;
    *this = temp;
  }

  void merge(Map& other) {
    for (iterator it = begin(); it != end(); ++it) {
      insertForMerge(it.getPtr());
    }
    other.root_ = nullptr;
    other.size_ = 0;
    delete other.fakeNode;
  }

  bool contains(const key_type& key) {
    node* res = findNode(key, root_);
    return (res) ? 1 : 0;
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
      delete root;
    }
  }

  node* findNode(const key_type& key, node* root) {
    if (size_ == 0 || root == 0 || root == fakeNode) {
      return nullptr;
    }
    if (root->data_.first == key) {
      return root;
    }
    return (root->data_.first > key) ? findNode(key, root->left_)
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
    } else if (map_compare(val->data_) > root->data_) {
      insertRecursive(root->right_, root, val, 1);
    } else {
      insertRecursive(root->left_, root, val, 0);
    }
  }

  void deleteBothChildren(iterator pos) {
    node* minRight = pos->right_->getMin();
    value_type val = minRight->data_;
    iterator recursive(minRight);
    erase(recursive);
    pos->data_ = val;
  }

  void deleteNoLeftChildren(iterator pos) {
    if (pos.getPtr() == root_) {
      root_ = pos->right_;
      root_->parent_ = nullptr;
      delete pos.getPtr();
    } else {
      iterator parent = pos->parent_;
      if (map_compare(*pos) > parent->data_) {  // если pos правый узел
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
      iterator newMax = --pos;
      iterator newRoot = pos->left_;

      newMax->right_ = fakeNode;
      fakeNode->parent_ = newMax.getPtr();
      root_ = newRoot.getPtr();
      newRoot->parent_ = nullptr;
      delete pos.getPtr();
    } else {
      iterator newPos = pos->left_;
      iterator parent = pos->parent_;
      if (pos->right_ == fakeNode) {
        iterator newMax = --pos;
        newMax->right_ = fakeNode;
        fakeNode->parent_ = newMax.getPtr();
      }
      if (map_compare(*pos) > parent->data_) {
        parent->right_ = newPos.getPtr();
      } else {
        parent->left_ = newPos.getPtr();
      }
      newPos->parent_ = parent.getPtr();
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
      if (map_compare(*pos) > pos->parent_->data_) {
        pos->parent_->right_ = nullptr;
      } else {
        pos->parent_->left_ = nullptr;
      }
      delete pos.getPtr();
    }
  }

  void insertForMerge(node* val) {
    if (empty()) {
      root_->data_ = val->data_;
      ++size_;
      delete val;
    } else {
      node* temp;
      // если узел с таким ключом уже есть
      if ((temp = findNode(val->data_.first, root_)) != nullptr) {
        delete val;
        return;
      }
      val->parent_ = val->left_ = val->right_ = nullptr;
      insertRecursive(root_, 0, val, 0);
      ++size_;
    }
  }
};
}  // namespace s21