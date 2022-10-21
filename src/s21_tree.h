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
  std::allocator<key_type> alloc_;  // выяснить зачем
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
      clearRecursive(root_);
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
    Set<value_type, cmp_type>::clearData_(this->root_);
    delete this->nill_;
    this->root_ = other.root_;
    this->size_ = other.size_;
    this->nill_ = other.nill_;
    other.root_ = nullptr;
    other.nill_ = nullptr;
    other.size_ = 0;
  }

  // доступ к элементу по ключу
  mapped_type& at(const key_type& key) {
    auto result = containsRef_(key);
    if (result.second == false)
      throw std::out_of_range("There is no pair with such key");
    return result.first;
  }
  // доступ к элементу по ключу (без исключений)
  mapped_type& operator[](const key_type& key) {
    try {
      return at(key);
    } catch (...) {
      Set<value_type, cmp_type>::insert({key, mapped_type()});
      return at(key);
    }
  }
  // вставка по паре
  std::pair<iterator, bool> insert(const value_type& value) {
    return Set<value_type, cmp_type>::insert({value.first, value.second});
  }
  // вставка по ключу и значению
  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return Set<value_type, cmp_type>::insert({key, obj});
  }
  // вставка или присваивание по ключу и значению
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    auto pair = Set<value_type, cmp_type>::insert({key, obj});
    if (pair.second == false) at(key) = obj;
    return pair;
  }

  // проверяет что в контейнере содержится пара с таким ключом
  bool contains(const Key& key) { return containsRef_(key).second; }
};