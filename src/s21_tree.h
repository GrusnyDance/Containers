#include <iostream>
#include <string>
#include <utility>  // initializer list

// принимает пару
template <typename Data>
class TreeNode {
 public:
  Data data_;
  TreeNode* left_;
  TreeNode* right_;
  TreeNode* parent_;

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
    } else if (temp->parent) {
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
      while (temp->parent_&& temp->parent->left_ = temp) {
        temp = temp->parent_;
      }
      temp = temp->parent_;
    }
  }

  TreeNode* getMinRight(TreeNode* current) {
    TreeNode* temp = current.getPtr();
    while (temp->left_) {
      temp = temp->left_;
    }
    return temp;
  }
};

// принимает пару, определяет как сравниваются ноды?? посмотреть как работает
// less который вызывается в оригинале
template <typename Data, bool isConst = 0>
class TreeIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using node_pointer = TreeNode<Data>*;
  using value_type = Data;
  // дружественный класс ноды
  friend class TreeNode<Data>;
  node_pointer ptr_;

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
    ptr_ = ptr_->next();
    return *this;
  }

  TreeIterator& operator--() {
    ptr_ = ptr_->prev();
    return *this;
  }

  node_pointer getPtr(){return ptr_};
  node_pointer operator->() { return (ptr_); }
  value_type operator*() { return (ptr_->data_); }
  bool operator==(const TreeIterator& other) { return (ptr_ == other.ptr_); }
  bool operator!=(const TreeIterator& other) { return (ptr_ != other.ptr_); }
};

template <typename Key, typename Value>
struct Compare {
  using myPair = std::pair<Key, Value>;
  myPair obj_;
  Compare(myPair obj){obj_ = obj};

  bool operator<(const myPair& a) const { return obj_.first < a.first; }
  bool operator>(const myPair& a) const { return obj_.first > a.first; }
  bool operator<=(const myPair& a) const { return obj_.first <= a.first; }
  bool operator>=(const myPair& a) const { return obj_.first >= a.first; }
  bool operator==(const myPair& a) const { return obj_.first == a.first; }
  bool operator!=(const myPair& a) const { return obj_.first != a.first; }
};

template <typename Key, typename Value>
class Map {
 protected:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<key_type, mapped_type>;
  using node = TreeNode<value_type>;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator<value_type>;
  using const_iterator = TreeIterator<value_type, 1>;
  using map_compare =
      Compare<key_type, mapped_type>;  // как функтор для сравнения пар

  node* root_;
  node* fakeNode;  // нода, на которую будет указывать end
  size_type size_ = 0;
  std::allocator<key_type> alloc_;  // для max_size

 public:
  friend class TreeNode<value_type>;
  friend class TreeIterator<value_type>;

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

  void copyRecursive(node* root, node* root_fake, node* other,
                     node* other_fake) {
    root->data_ = other->data_;
    if (other->left_ != nullptr) {
      node* temp = new node();
      temp->parent_ = root;
      root->left_ = temp;
      MapCopy(temp, root_fake, other->left_, other_fake);
    }
    if (other->right_ != nullptr) {
      if (other->right_ == other_fake) {
        root->right_ = root_fake;
        root_fake->parent_ = root;
      } else {
        node* temp = new node();
        temp->parent_ = root;
        root->right_ = temp;
        MapCopy(temp, root_fake, other->right_, other_fake);
      }
    }
  }

  Map(Set&& other) : Map() {  // перемещение
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
      clearRecursive(root_);  // проверить находит ли this
      root_ = fakeNode = nullptr;
      size_ = 0;
    }
    if (fakeNode) delete fakeNode;
    if (root_) delete root_;
  }

  void clearRecursive(node* root) {
    if (root) {
      if (root->left_) clearRecursive(root->left_);
      if (root->right) clearRecursive(root->right);
      delete root;
    }
  }

  // оператор присваивания перемещением
  void operator=(Map&& other) {
    if (this == &other) return *this;
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

  node* findNode(const key_type& key, node* root) {
    if (size_ == 0 || root == 0 || root == this->fakeNode) {
      return nullptr;
    }
    if (root->data_.first == key) {
      return root;
    }
    return (root->data_.first > key) ? findNode(key, root->left)
                                     : findNode(key, root->right);
  }

  // присваивает если ключ не найден
  mapped_type& operator[](const key_type& key) {
    try {
      return at(key);
    } catch (...) {  // ловит любое исключение
      insert(value_type(key, 0));
      return at(key);
    }
  }

  iterator begin() {
    iterator result(root_);
    return result;
  }
  iterator end() {
    iterator result(fakeNode);
    return result;
  }
  const_iterator begin() const {
    const_iterator result(root_);
    return result;
  }
  const_iterator end() const {
    const_iterator result(fakeNode);
    return result;
  }

  bool empty() const { return size_ = 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return alloc_.max_size(); }

  // inserts node and returns iterator to where the element is in the container
  // and bool denoting whether the insertion took place
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
      ++size_;
    }
    if (map_compare(val->data_) > root->data_) {
      insertRecursive(root->right_, root, val, 1);
    } else {
      insertRecursive(root->right_, root, val, 0);
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

  void deleteBothChildren(iterator pos) {
    node* minRight = getMinRight(pos->right_);
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
      if (map_compare(*pos) > parent_->data_) {  // если pos правый узел
        parent->right_ = pos->right_;
      } else {
        parent->left_ = pos->right_;
      }
      pos->right_->parent = parent;
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
      if (map_compare(*pos) > parent_->data_) {
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
      pos->parent->right_ = fakeNode;
      delete pos.getPtr();
    } else {
      if (map_compare(*pos) > pos->parent_->data_) {
        pos->parent_->right_ = nullptr;
      } else {
        pos_ > parent_->left_ = nullptr;
      }
      delete pos.getPtr();
    }
  }

  bool contains(const key_type& key) {
    node* res = findNode(key, root_);
    return (res) ? 1 : 0;
  }
};