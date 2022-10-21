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

  node_pointer operator->() { return (ptr_); }  // какая то хуйня, мб убрать
  value_type operator*() { return (ptr_->data_); }
  bool operator==(const TreeIterator& other) { return (ptr_ == other.ptr_); }
  bool operator!=(const TreeIterator& other) { return (ptr_ != other.ptr_); }
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

  node* root_;
  node* fakeNode;  // нода, на которую будет указывать end
  size_type size_ = 0;
  std::allocator<key_type> alloc_;  // для max_size
  Compare<key_type, value_type> mapCompare;  // написать класс сравнения

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
    if (size_ > 0) {
      clearRecursive(root_);  // написать отдельную функцию clear по таску
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
};