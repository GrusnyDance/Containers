#ifndef _SRC_S21_LIST_H_
#define _SRC_S21_LIST_H_

#include <initializer_list>
#include <limits>

#include "s21_sort.h"

namespace s21 {

template <class T>
class list;

template <class T>
class ListIterator;

template <class T>
struct Node {
    T value;
    Node *prev = nullptr;
    Node *next = nullptr;
    void addPrev(Node<T> *add) {
        add->next = this;
        add->prev = prev;
        prev->next = add;
        prev = add;
    }
    void addNext(Node<T> *add) {
        add->next = next;
        add->prev = this;
        next->prev = add;
        next = add;
    }
    Node<T> *addPrev(const T value_) {
        Node *add = new Node;
        add->value = value_;
        addPrev(add);
        return add;
    }
    Node<T> *addNext(const T value_) {
        Node *add = new Node;
        add->value = value_;
        addNext(add);
        return add;
    }
    Node<T> *pop() {  // return next
        Node<T> *ret = next;
        prev->next = next;
        next->prev = prev;
        delete this;
        return ret;
    }
};

template <class T>
class ListConstIterator;

template <class T>
class ListIterator {
    private:
        friend class list<T>;
        friend class ListConstIterator<T>;
        Node<T> *ptr = nullptr;
    public:
        T& operator*() {
            return ptr->value;
        }
        ListIterator& operator++(int) {
            ptr = ptr->next;
            return *this;
        }
        ListIterator& operator--(int) {
            ptr = ptr->prev;
            return *this;
        }
        bool operator!=(ListIterator<T> other) {
            if (ptr == other.ptr) return false;
            return true;
        }
        bool operator==(ListIterator<T> other) {
            if (ptr == other.ptr) return true;
            return false;
        }
        ListIterator(Node<T> *node)  : ptr(node) {};
};

template <class T>
class ListConstIterator {
    private:
        friend class list<T>;
        Node<T> *ptr = nullptr;
    public:
        const T& operator*() {
            return ptr->value;
        }
        ListConstIterator& operator++(int) {
            ptr = ptr->next;
            return *this;
        }
        ListConstIterator& operator--(int) {
            ptr = ptr->prev;
            return *this;
        }
        bool operator!=(ListConstIterator<T> other) {
            if (ptr == other.ptr) return false;
            return true;
        }
        bool operator==(ListConstIterator<T> other) {
            if (ptr == other.ptr) return true;
            return false;
        }
        ListConstIterator(Node<T> *node) : ptr(node) {}
        ListConstIterator(ListIterator<T> other) : ptr(other.ptr) {}
        ListConstIterator &operator=(ListIterator<T> other) {
            ptr = other.ptr;
            return this;
        }

};

template <class T>
class list {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = ListIterator<T>;
        using const_iterator = ListConstIterator<T>;
        using size_type = std::size_t;
        using node = Node<T>;
    private:
        node *head = nullptr; // front
        node *root = nullptr; // back
        node *fake = nullptr;
        size_type size_ = 0;
        void closedFake() {
            fake->next = fake;
            fake->prev = fake;
            head = fake;
            root = fake;
        }
        void fakeAllocate() {
            fake = new node;
            closedFake();
        }
        template<class sw>
        void swap(sw *a, sw *b) {
            sw buff = *a;
            *a = *b;
            *b = buff;
        }
    public:
        list() : size_(0) {
            fakeAllocate();
        }
        list(size_type n) : size_(n) {
            fakeAllocate();
            node *prev_ = fake;
            for (int k = 0; k < n; k++) {
                node *add = new node;
                prev_->next = add;
                add->prev = prev_;
                prev_ = add;
                if (k == 0) head = add;
                if (k == n - 1) {
                    root = add;
                    root->next = fake;
                }
            }
        }
        list(std::initializer_list<value_type> const &items) {
            fakeAllocate();
            for (const auto &add : items) push_back(add);
            head = fake->next;
            root = fake->prev;
        }
        list(const list<value_type> &l) : size_(l.size_) {  // copy
            fakeAllocate();
            node *copy = l.head;
            node *prev_ = fake;
            for (size_type k = 0; k < size_; k++) {
                node *add = prev_->addNext(copy->value);
                if (k == 0) head = add;
                if (k == size_ - 1) root = add;
                prev_ = add;
                copy = copy->next;
            }
        }
        list &operator=(list<value_type> &&l) noexcept {  // move
            fake = l.fake;
            head = l.head;
            root = l.root;
            l.fakeAllocate();
            size_ = l.size_;
            l.size_ = 0;
            return *this;
        }
        list(list<value_type> &&l) {  // move
            fake = l.fake;
            head = l.head;
            root = l.root;
            l.fakeAllocate();
            size_ = l.size_;
            l.size_ = 0;
        }
        ~list() {
            while (head != fake) {
                node *del = head;
                head = head->next;
                delete del;
            }
            delete fake;
        }
        list &operator=(const list<value_type> &l) {  // copy
            size_ = l.size_;
            fakeAllocate();
            node *copy = l.head;
            node *prev_ = fake;
            for (size_type k = 0; k < size_; k++) {
                node *add = prev_->addNext(copy->value);
                if (k == 0) head = add;
                if (k == size_ - 1) root = add;
                prev_ = add;
                copy = copy->next;
            }
            return *this;
        }
        bool operator==(list<value_type> other) const {
            if (size_ == other.size_) {
                node *Tcheck = head;
                node *Ocheck = other.head;
                while (Tcheck != fake) {
                    if (Tcheck->value != Ocheck->value) return false;
                    Tcheck = Tcheck->next;
                    Ocheck = Ocheck->next;
                }
                return true;
            }
            return false;
        }
        const_reference front() {
            return head->value;
        }
        const_reference back() {
            return root->value;
        }
        iterator begin() {
            iterator begin_iter(head);
            return begin_iter;
        }
        iterator end() {
            iterator fake_iter(fake);
            return fake_iter;
        }
        bool empty() {
            if ((head == fake && root == fake) || size_ == 0) return true;
            return false;
        }
        size_type size() {
            return size_;
        }
        size_type max_size() {
            return (std::numeric_limits<size_type>::max() / sizeof(node) / 2);  // include <limits>
        }
        void clear() {
            node *del = head;
            for (size_type k = 0; k < size_; k++) {
                head = head->next;
                delete del;
                del = head;
            }
            closedFake();
            size_ = 0;
        }
        iterator insert(iterator pos, const_reference value) {
            node *add = pos.ptr->addPrev(value);
            if (add->prev == fake) head = add;
            if (add->next == fake) root = add;
            size_++;
            pos--;
            return pos;
        }
        iterator erase(iterator pos) {
            // if (empty()) return;
            if (pos.ptr == head) head = pos.ptr->next;
            if (pos.ptr == root) root = pos.ptr->prev;
            pos.ptr->next->prev = pos.ptr->prev;
            pos.ptr->prev->next = pos.ptr->next;
            iterator ret = pos.ptr->next;
            delete pos.ptr;
            size_--;
            return ret;
        }
        void push_back(const_reference value) {
            root = fake->addPrev(value);
            if (fake == head) head = root;
            size_++;
        }
        void pop_back() {
            if (empty()) return;
            if (size_ == 1) {
                clear();
                return;
            }
            root = root->pop()->prev;
            size_--;
            if (size_ == 1) head = root;
        }
        void push_front(const_reference value) {
            head = fake->addNext(value);
            if (fake == root) root = head;
            size_++;
        }
        void pop_front() {
            if (empty()) return;
            if (size_ == 1) {
                clear();
                return;
            }
            head = head->pop();
            size_--;
            if (size_ == 1) root = head;
        }
        void swap(list<T>& other) {
            swap<node*>(&head, &other.head);
            swap<node*>(&root, &other.root);
            swap<node*>(&fake, &other.fake);
            swap<size_type>(&size_, &other.size_);
        }
        void merge(list& other) {
            node *other_ = other.head;
            node *this_ = head;
            while (other_ != other.fake) {
                if (this_ == fake || (other_->value < this_->value)) {
                    other_ = other_->next;
                    this_->addPrev(other_->prev);
                } else {
                    this_ = this_->next;
                }
            }
            head = fake->next;
            root = fake->prev;
            other.closedFake();
            size_ += other.size_;
            other.size_ = 0;
        }
        void splice(const_iterator pos, list& other) {
            pos.ptr->prev->next = other.head;
            other.head->prev = pos.ptr->prev;
            pos.ptr->prev = other.root;
            other.root->next = pos.ptr;
            if (pos.ptr == head) head = other.head;
            if (pos.ptr == fake) root = other.root;
            other.closedFake();
            size_ += other.size_;
            other.size_ = 0;
        }
        void reverse() {
            node *this_ = head;
            swap<node*>(&head, &root);
            for (int k = 0; k <= (int)size_; k++) {
                swap<node*>(&this_->next, &this_->prev);
                this_ = this_->prev;
            }
        }
        void unique() {
            node *this_ = head;
            while (this_ != fake) {
                const_reference S = this_->value;
                this_ = this_->next;
                while (S == this_->value && this_ != fake) {
                    this_ = this_->pop();
                    size_--;
                    if (this_ == fake) {
                        root = this_->prev;
                        break;
                    }
                }
            }
        }
        void sort() {
            iterator start(head);
            iterator end(root);
            QSort<iterator, value_type>(start, end);
        }
};

}  // namespace s21

#endif // _SRC_S21_LIST_H_
