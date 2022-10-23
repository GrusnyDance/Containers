// #include "map.hpp"

namespace s21 {

template <typename Key, typename Value>
Map<Key, Value>::Map() {
  fakeNode = new node();  // скобки для вызова дефолтного конструктора
  root_ = new node();
  root_->right_ = fakeNode;
  fakeNode->parent_ = root_;
}

// инициализация листом
template <typename Key, typename Value>
Map<Key, Value>::Map(std::initializer_list<key_type> const& items) : Map() {
  for (auto iter = items.begin(); iter != items.end(); ++iter) insert(*iter);
}

template <typename Key, typename Value>
Map<Key, Value>::Map(const Map& other) : Map() {  // копирование
  if (other.size_ > 0) {
    copyRecursive(root_, fakeNode, other.root_, other.fakeNode);
    size_ = other.size_;
  }
}

template <typename Key, typename Value>
Map<Key, Value>::Map(Map&& other) : Map() {  // перемещение
  delete fakeNode;
  delete root_;
  root_ = other.root_;
  size_ = other.size_;
  fakeNode = other.fakeNode;
  other.root_ = nullptr;
  other.fakeNode = nullptr;
  other.size_ = 0;
}

template <typename Key, typename Value>
Map<Key, Value>::~Map() {  // деструктор
  clear();
}

template <typename Key, typename Value>
void Map<Key, Value>::clear() {
  if (size_ > 0) {
    clearRecursive(root_);
    root_ = fakeNode = nullptr;
    size_ = 0;
  }
  if (fakeNode) delete fakeNode;
  if (root_) delete root_;
}

// оператор присваивания перемещением
template <typename Key, typename Value>
void Map<Key, Value>::operator=(Map&& other) {
  if (this == &other) return;
  clearRecursive(root_);

  root_ = other.root_;
  size_ = other.size_;
  fakeNode = other.fakeNode;
  other.root_ = other.fakeNode = nullptr;
  other.size_ = 0;
}

// проверяет, существует ли ключ
template <typename Key, typename Value>
typename Map<Key, Value>::mapped_type& Map<Key, Value>::at(
    const key_type& key) {
  node* res = findNode(
      key,
      root_);  // не сработает без передачи вызывающего объекта тк рекурсия?
  if (!res) {
    throw std::out_of_range("There is no such key");
  }
  return res->data_.second;
}

// присваивает если ключ не найден
template <typename Key, typename Value>
typename Map<Key, Value>::mapped_type& Map<Key, Value>::operator[](
    const key_type& key) {
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

template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::begin() {
  node* temp = root_->getMin();
  iterator result(temp);
  return result;
}

template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::end() {
  iterator result(fakeNode);
  return result;
}

// template <typename Key, typename Value>
// Map<Key, Value>::const_iterator Map<Key, Value>::begin() const {
//   node* temp = root_->getMin();
//   const_iterator result(temp);
//   return result;
// }
// template <typename Key, typename Value>
// Map<Key, Value>::const_iterator Map<Key, Value>::end() const {
//   const_iterator result(fakeNode);
//   return result;
// }

template <typename Key, typename Value>
typename Map<Key, Value>::size_type Map<Key, Value>::max_size()
    const {  // it works i have no idea how
  return std::numeric_limits<size_type>::max() /
         (sizeof(value_type) + 3 * sizeof(node*) + 8 * sizeof(bool)) / 2;
}

// bool показывает произошла ли вставка
template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool> Map<Key, Value>::insert(
    const value_type& value) {
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

template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool> Map<Key, Value>::insert(
    const key_type& key, const mapped_type& obj) {
  std::pair<key_type, mapped_type> res(key, obj);
  return insert(res);
}

template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool>
Map<Key, Value>::insert_or_assign(const key_type& key, const mapped_type& obj) {
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

template <typename Key, typename Value>
void Map<Key, Value>::erase(iterator pos) {  // 4 сценария
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

template <typename Key, typename Value>
void Map<Key, Value>::swap(Map& other) {
  Map temp = other;
  other = *this;
  *this = temp;
}

template <typename Key, typename Value>
void Map<Key, Value>::merge(Map& other) {
  for (iterator it = begin(); it != end(); ++it) {
    insertForMerge(it.getPtr());
  }
  other.root_ = nullptr;
  other.size_ = 0;
  delete other.fakeNode;
}

template <typename Key, typename Value>
bool Map<Key, Value>::contains(const key_type& key) {
  node* res = findNode(key, root_);
  return (res) ? 1 : 0;
}

template <typename Key, typename Value>
void Map<Key, Value>::copyRecursive(node* root, node* root_fake, node* other,
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

template <typename Key, typename Value>
void Map<Key, Value>::clearRecursive(node* root) {
  if (root) {
    if (root->left_) clearRecursive(root->left_);
    if (root->right_) clearRecursive(root->right_);
    delete root;
  }
}

template <typename Key, typename Value>
typename Map<Key, Value>::node* Map<Key, Value>::findNode(const key_type& key,
                                                          node* root) {
  if (size_ == 0 || root == 0 || root == fakeNode) {
    return nullptr;
  }
  if (root->data_.first == key) {
    return root;
  }
  return (root->data_.first > key) ? findNode(key, root->left_)
                                   : findNode(key, root->right_);
}

template <typename Key, typename Value>
void Map<Key, Value>::insertRecursive(node* root, node* parent, node* val,
                                      bool right) {
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

template <typename Key, typename Value>
void Map<Key, Value>::deleteBothChildren(iterator pos) {
  node* minRight = pos->right_->getMin();
  value_type val = minRight->data_;
  iterator recursive(minRight);
  erase(recursive);
  pos->data_ = val;
}

template <typename Key, typename Value>
void Map<Key, Value>::deleteNoLeftChildren(iterator pos) {
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

template <typename Key, typename Value>
void Map<Key, Value>::deleteNoRightChildren(iterator pos) {
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

template <typename Key, typename Value>
void Map<Key, Value>::deleteNoChildren(iterator pos) {
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

template <typename Key, typename Value>
void Map<Key, Value>::insertForMerge(node* val) {
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
}  // namespace s21