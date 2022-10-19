#ifndef _SRC_S21_VECTOR_H_
#define _SRC_S21_VECTOR_H_

#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

namespace s21 {

template <class T>
class iterator_vector;

template <class T>
class const_iterator_vector;

template <class T>
class vector {
    // value_type	T defines the type of an element (T is template parameter)
    using value_type = T;

    // pointer T*
    using pointer = T*;

    // reference T & defines the type of the reference to an element
    using reference = value_type&;

    // const_reference const T & defines the type of the constant reference
    using const_reference = const value_type&;

    // iterator	T * or internal class VectorIterator<T> defines the type for iterating through the container
    using iterator = iterator_vector<T>;

    // const_iterator const T * or internal class VectorConstIterator<T> defines the constant type for iterating through the container
    using const_iterator = const_iterator_vector<T>;

    // size_type size_t defines the type of the container size (standard type is size_t)
    using size_type = std::size_t;

    private:
    value_type* first_;
    size_type size_;
    size_type alloc_size_;

    public:
    // Constructors, assigment opeartors
    vector() {
        first_ = nullptr;
        size_ = 0;
        alloc_size_ = 0;
    }

    vector(size_type n) {
        first_ = new value_type[n];
        size_ = n;
        alloc_size_ = n;
    }

    vector(std::initializer_list<value_type> const &items) : first_(nullptr) {
        size_ = alloc_size_ = items.size();
        if (size_) {
            first_ = new value_type[size_];
            std::copy(items.begin(), items.end(), first_);
        } else {
            first_ = nullptr;
        }
    }

    vector(const vector &v)
    : size_(v.size_), alloc_size_(v.alloc_size_) {
        if (size_) {
            first_ = new value_type[size_];
            std::copy(v.first_, v.first_ + (v.size_ - 1), first_);
        } else {
            first_ = nullptr;
        }
    }

    // Не работает
    vector(vector &&v) : size_(v.size_), alloc_size_(v.alloc_size_) {
        first_ = v.first_;
        v.first_ = nullptr;
        v.size_ = 0;
        v.alloc_size_ = 0;
    }

    ~vector() {
        if (first_ != nullptr) {
            delete[] first_;
        }
    }

    vector& operator=(vector &&v);
    vector& operator=(const vector& other); // Пока не знаю как и зачем это нужно

    // Methods for acces of elements

    // access specified element with bounds checking
    reference at(size_type pos) {
        return *(first_ + pos);
    }

    // access specified element
    reference operator[](size_type pos) {
        return *(first_ + pos);
    }

    //	access the first element
    const_reference front() { return *first_; }

    // access the last element
    const_reference back() { return *(first_ + size_ - 1) ;}

    // direct access to the underlying array
    T* data() { return first_; }

    // Iterators
    iterator begin() { return iterator(first_); }
    iterator end() { return iterator(first_ + size_); }
    const_iterator begin() const { return const_iterator(first_); }
    const_iterator end() const { return const_iterator(first_ + size_); }

    // Methods for capacity
    
    // checks whether the container is empty
    [[nodiscard]] bool empty() {
        if (size_ == 0) {
        return true;
        }
        return false;
    }
    
    // returns the number of elements
    [[nodiscard]] size_type size() {
        return size_;
    }

    // returns the maximum possible number of elements
    [[nodiscard]] size_type max_size();

    // allocate storage of size elements and copies current array elements to a newely allocated array
    void reserve(size_type size) {
        if (size_ > alloc_size_) {
            size_type copyHelper = alloc_size_;
            alloc_size_ = size;
            T* tmp = new T[alloc_size_];
            std::copy(first_, first_ + copyHelper, tmp);
            delete[] first_;
            first_ = tmp;
        }
    }
     
    // returns the number of elements that can be held in currently allocated storage
    size_type capacity() {
        return alloc_size_;
    }

    // reduces memory usage by freeing unused memory
    void shrink_to_fit(size_type newSize) {
        if (newSize < size_) {
            T* tmp = new T[newSize];
            std::memmove(tmp, first_, size_ * sizeof(T));
            delete[] first_;
            first_ = tmp;
            size_ = newSize;
        }
    }

    // Methods for changing container
    
    // clears the contents
    void clear() {
        this->~vector();
    }

    // inserts elements into concrete pos and returns the iterator that points to the new element
    iterator insert(iterator pos, const_reference value) {
        size_++;
        if (first_ == nullptr) {
            alloc_size_ = 1;
            first_ = new value_type[value];
            first_ = *value;
            return iterator(pos);
        }

        if (size_ <= alloc_size_) {
            // std::memmove(pos.ptr_ + 1, pos.ptr_,
            //     (size_ - 1) * sizeof(T) - (pos.ptr_ - front_) * sizeof(T));
            // *(pos.ptr_) = value;
        }
    }
    
    // erases element at pos
    void erase(iterator pos);

    // adds an element to the end
    void push_back(const_reference value) {

    }

    // removes the last element
    void pop_back();

    // swaps the contents
    void swap(vector& other) {
        std::swap(other.size_, size_);
        std::swap(other.alloc_size_, alloc_size_);
        std::swap(other.first_, first_);
    }
};
} // namespace s21

#endif // _SRC_S21_VECTOR_H_

// Пока не нашел нужно ли где-то их применять или нет
// ========================================================================
// using const_pointer = const T*;
// using allocator_type = Allocator;
// using difference_type = std::ptrdiff_t;
// using pointer = std::allocator_traits<Allocator>::pointer;
// using const_pointer = std::allocator_traits<Allocator>::const_pointer;
// ========================================================================
