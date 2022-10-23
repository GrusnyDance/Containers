// #include "map.hpp"

namespace s21 {

template <typename Data>
TreeNode<Data>::TreeNode(Data data, TreeNode* parent, TreeNode* left,
                         TreeNode* right) {
  data_ = data;
  parent_ = parent;
  left_ = left;
  right_ = right;
}

// оператор присваивания копированием
template <typename Data>
TreeNode<Data>& TreeNode<Data>::operator=(const TreeNode& other) {
  if (this != &other) {
    data_ = other.data_;
    parent_ = other.parent_;
    left_ = other.left_;
    right_ = other.right_;
  }
  return *this;
}

// функции для поиска предыдущего и следующего узла, чтобы итерироваться в обе
// стороны
template <typename Data>
TreeNode<Data>* TreeNode<Data>::nextNode() {  // ищет следующий по значению узел
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

template <typename Data>
TreeNode<Data>* TreeNode<Data>::previousNode() {
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

template <typename Data>
TreeNode<Data>* TreeNode<Data>::getMin() {
  TreeNode* temp = this;
  while (temp->left_) {
    temp = temp->left_;
  }
  return temp;
}
}  // namespace s21