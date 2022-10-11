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

    // reference	T & defines the type of the reference to an element
    using reference = value_type&;

    // const_reference	const T & defines the type of the constant reference
    using const_reference = const value_type&;

    // iterator	T * or internal class VectorIterator<T> defines the type for iterating through the container
    using iterator = iterator_vector<T>;

    // const_iterator	const T * or internal class VectorConstIterator<T> defines the constant type for iterating through the container
    using const_iterator = const_iterator_vector<T>;

    // size_type	size_t defines the type of the container size (standard type is size_t)
    using size_type = std::size_t;

    private:
    
    public:
    // Constructors, assigment opeartors
    vector();
    vector(size_type n);
    vector(std::initializer_list<value_type> const &items)
    vector(const vector &v);
    vector(vector &&v);
    ~vector();

    vector& operator=(vector &&v);
    vector& operator=(const vector& other); // Пока не знаю как и зачем это нужно

    // Methods for acces of elements
    reference at(size_type pos);  // access specified element with bounds checking
    reference operator[](size_type pos); // access specified element
    const_reference front(); //	access the first element
    const_reference back(); // access the last element
    T* data(); // direct access to the underlying array

    // Iterators
    iterator begin(); // { return iterator(front_); }
    iterator end(); // { return iterator(front_ + size_); }
    const_iterator begin() const; // { return const_iterator(front_); }
    const_iterator end() const; // { return const_iterator(front_ + size_); }

    // Methods for capacity
    bool empty(); // checks whether the container is empty
    size_type size(); // returns the number of elements
    size_type max_size(); // returns the maximum possible number of elements
    void reserve(size_type size); // allocate storage of size elements and copies current array elements to a newely allocated array
    size_type capacity(); // returns the number of elements that can be held in currently allocated storage
    void shrink_to_fit(); // reduces memory usage by freeing unused memory

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
// using pointer = T*;
// using const_pointer = const T*;
// using allocator_type = Allocator;
// using difference_type = std::ptrdiff_t;
// using pointer = std::allocator_traits<Allocator>::pointer;
// using const_pointer = std::allocator_traits<Allocator>::const_pointer;
// ========================================================================
