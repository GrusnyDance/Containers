#ifndef _SRC_S21_LIST_H_
#define _SRC_S21_LIST_H_

#include <initializer_list>
#include <limits>

#include "s21_sort.h"

#define R_PREV 1
#define R_NEXT 0

namespace s21 {

template <class T>
class list;

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
        Node<T> *ptr = nullptr;
    public:
        T& operator*() { return ptr->value; }
        ListIterator operator++(int) {
            ptr = ptr->next;
            return *this;
        }
        ListIterator operator--(int) {
            ptr = ptr->prev;
            return *this;
        }
        ListIterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        ListIterator& operator--() {
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
class ListConstIterator: public ListIterator<T> {
    public:
        const T& operator*() { return ListIterator<T>::operator*(); }
        ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
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
        node *head = nullptr;  // front begin
        node *root = nullptr;  // back
        node *fake = nullptr;  // end
        size_type size_ = 0;
        node *addNode(node *base, const T *value, bool route) {
            node *add = new node;
            if (value != nullptr) add->value = *value;
            route ? base->addPrev(add) : base->addNext(add);
            rootHead();
            size_++;
            return add;
        }
        node *pop(node *waste) {  // return next
            if (empty()) return waste;
            node *ret = waste->pop();
            size_--;
            rootHead();
            return ret;
        }
        void closedFake() {
            fake->next = fake;
            fake->prev = fake;
            head = fake;
            root = fake;
            size_ = 0;
        }
        void fakeAllocate() {
            fake = new node;
            closedFake();
        }
        void rootHead() {
            head = fake->next;
            root = fake->prev;
        }
        template<class sw>
        void swap(sw *a, sw *b) {
            sw buff = *a;
            *a = *b;
            *b = buff;
        }
        void del() {  // does not remove the fake node
            while (head != fake) {
                node *del = head;
                head = head->next;
                delete del;
            }
        }
    public:
        list() : size_(0) { fakeAllocate(); }
        list(size_type n) {
            fakeAllocate();
            for (int k = 0; k < n; k++) addNode(fake, nullptr, R_PREV);
        }
        list(std::initializer_list<value_type> const &items) {
            fakeAllocate();
            for (const auto &add : items) push_back(add);
        }
        list(const list<value_type> &l) {  // copy
            fakeAllocate();
            for (auto i : l) addNode(fake, &i, R_PREV);
        }
        list(list<value_type> &&l) : fake(l.fake), head(l.head), root(l.root), size_(l.size_) {  // move
            l.fakeAllocate();
        }
        list &operator=(list<value_type> &&l) {  // move
            del();
            delete fake;
            fake = l.fake;
            rootHead();
            size_ = l.size_;
            l.fakeAllocate();
            return *this;
        }
        ~list() {
            del();
            delete fake;
        }
        list &operator=(const list<value_type> &l) {  // copy
            fakeAllocate();
            for (auto i : l) addNode(fake, &i, R_PREV);
            return *this;
        }
        bool operator==(list<value_type> other) const {
            if (size_ == other.size_) {
                for (node *i = head, *j = other.head; i != fake; i = i->next, j = j->next) {
                    if (i->value != j->value) return false;
                }
                return true;
            }
            return false;
        }
        const_reference front() const { return head->value; }
        const_reference back() const { return root->value; }
        iterator begin() { return iterator(head); }
        const_iterator begin() const { return const_iterator(head); }
        iterator end() { return iterator(fake); }
        const_iterator end() const { return const_iterator(fake); }
        bool empty() const {
            if ((head == fake && root == fake) || size_ == 0) return true;
            return false;
        }
        size_type size() const { return size_; }
        size_type max_size() const {
            return (std::numeric_limits<size_type>::max() / sizeof(node) / 2);  // include <limits>
        }
        void clear() {
            del();
            closedFake();
        }
        iterator insert(iterator pos, const_reference value) {
            return iterator(addNode(pos.ptr, &value, R_PREV));
        }
        iterator erase(iterator pos) { return iterator(pop(pos.ptr)); }
        void push_back(const_reference value) { addNode(fake, &value, R_PREV); }
        void pop_back() { pop(root); }
        void push_front(const_reference value) { addNode(fake, &value, R_NEXT); }
        void pop_front() { pop(head); }
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
            rootHead();
            size_ += other.size_;
            other.closedFake();
        }
        void splice(const_iterator pos, list& other) {
            pos.ptr->prev->next = other.head;
            other.head->prev = pos.ptr->prev;
            pos.ptr->prev = other.root;
            other.root->next = pos.ptr;
            rootHead();
            size_ += other.size_;
            other.closedFake();
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
                while (this_ != fake && S == this_->value) this_ = pop(this_);
            }
        }
        void sort() {
            iterator start(head);
            iterator end(root);
            QSort<iterator, value_type>(start, end);
        }
        iterator emplace(iterator pos, value_type arg) { return insert(pos, arg); }
        template<class... Args>
        iterator emplace(const_iterator pos, value_type first, Args&&... args) {
            return emplace(insert(pos, first)++, args...);  // return iterator(last of args)
            // return insert(emplace(pos, args...), first);  // return iterator(first of args)
        }
        void emplace_back(value_type first) { push_back(first); }
        template<class... Args>
        void emplace_back(value_type first, Args&&... args) {
            push_back(first);
            emplace_back(args...);
        }
        void emplace_front(value_type first) { push_front(first); }
        template<class... Args>
        void emplace_front(value_type first, Args&&... args) {
            push_front(first);
            emplace_front(args...);
        }
};

}  // namespace s21

#endif // _SRC_S21_LIST_H_
