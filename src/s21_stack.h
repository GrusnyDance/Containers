#ifndef _SRC_S21_STACK_H_
#define _SRC_S21_STACK_H_

#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

namespace s21 {
template <class T> struct node {
  node *next;
  T value;
};

template <class T> class stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = node<T>;

public:
  // constructors
  stack() : head_(nullptr), size_(0) {}

  stack(std::initializer_list<value_type> const &items)
      : head_(nullptr), size_(0) {
    for (auto i : items) {
      this->push(i);
    }
  }

  stack(const stack &s) : head_(nullptr), size_(0) {
    stack<value_type> help;
    Node *n = s.head_;
    while (n != nullptr) {
      help.push(n->value);
      n = n->next;
    }

    while (help.size_ != 0) {
      this->push(help.top());
      help.pop();
    }
  }

  stack(stack &&s) {
    head_ = s.head_;
    size_ = s.size_;
    s.head_ = nullptr;
    s.size_ = 0;
  }

  ~stack() {
    while (size_ != 0) {
      this->pop();
    }
  }

  stack &operator=(stack &s) {
    stack<value_type> help;
    Node *n = s.head_;
    while (n != nullptr) {
      help.push(n->value);
      n = n->next;
    }

    while (help.size_ != 0) {
      this->push(help.top());
      help.pop();
    }
  }

  stack &operator=(stack &&s) {
    if (s == nullptr)
      return nullptr;

    head_ = s.head_;
    size_ = s.size_;
    s.head_ = nullptr;
    s.size_ = 0;
  }

  // Methods

  const_reference top() { return head_->value; }

  void push(const_reference value) {
    size_++;
    Node *tmp = new Node();
    tmp->value = value;
    tmp->next = head_;
    head_ = tmp;
  }

  void pop() {
    if (size_ == 0 || head_ == nullptr) {
      return;
    }

    size_--;
    Node *out;
    out = head_;
    head_ = head_->next;
    delete out;
  }

  void swap(stack &s) {
    std::swap(this->head_, s.head_);
    std::swap(this->size_, s.size_);
  }

private:
  Node *head_;
  size_type size_;
};
} // namespace s21
#endif // _SRC_S21_STACK_H_
