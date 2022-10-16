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
    reference at(size_type pos);  // access specified element with bounds checking

    // access specified element
    reference operator[](size_type pos) {
        return *(first_ + pos);
    }

    //	access the first element
    const_reference front() { return *first_; }

    // access the last element
    const_reference back() { return *(first_ + size_ - 1) ;}

    // direct access to the underlying array
    T* data();





    // Iterators
    iterator begin() { return iterator(first_); }
    iterator end() { return iterator(first_ + size_); }
    const_iterator begin() const { return const_iterator(first_); }
    const_iterator end() const { return const_iterator(first_ + size_); }





    // Methods for capacity
    
    // checks whether the container is empty
    bool empty();
    
    // returns the number of elements
    size_type size() {
        return size_;
    }

    // returns the maximum possible number of elements
    size_type max_size();

    // allocate storage of size elements and copies current array elements to a newely allocated array
    void reserve(size_type size);
     
    // returns the number of elements that can be held in currently allocated storage
    size_type capacity() {
        return alloc_size_;
    }

    // reduces memory usage by freeing unused memory
    void shrink_to_fit();




    // Methods for changing container
    void clear(); // clears the contents
    iterator insert(iterator pos, const_reference value); // inserts elements into concrete pos and returns the iterator that points to the new element
    void erase(iterator pos); // erases element at pos
    void push_back(const_reference value); // adds an element to the end
    void pop_back(); // removes the last element
    void swap(vector& other); // swaps the contents
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
