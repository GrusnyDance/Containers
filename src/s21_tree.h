#include <iostream>

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

  TreeIterator(){ptr_ = nullptr};
  TreeIterator(node_pointer ptr){ptr_ = ptr};
  TreeIterator(const TreeIterator& other) : { *this = other; }
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