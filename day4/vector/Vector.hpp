#ifndef _VECTOR_HPP__
#define _VECTOR_HPP__

#include <iostream>
#include <initializer_list>

namespace vhuk {

template <typename T> class Vector;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& v);

template <typename T>
class Vector
{
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

public:
    class const_iterator {
        friend Vector<value_type>;
    public:
        const_iterator(); //O(1)
        const_iterator(const const_iterator& rhv); //O(1)
        ~const_iterator(); //O(1)
        const const_iterator& operator=(const const_iterator& rhv); //O(1)
        const value_type& operator*() const; //O(1)
        const value_type* operator->() const; //O(1)
        
        const const_iterator& operator++(); //O(1)
        const const_iterator operator++(value_type); //O(1)
        const const_iterator& operator--(); //O(1)
        const const_iterator operator--(value_type); //O(1)
        const const_iterator operator+=(const size_type i); //O(1)
        const const_iterator operator-=(const size_type i); //O(1)
        const const_iterator operator+(const size_type i) const; //O(1)
        const const_iterator operator-(const size_type i) const; //O(1)
        bool operator==(const const_iterator& rhv) const; //O(1)
        bool operator!=(const const_iterator& rhv) const; //O(1)
        bool operator<(const const_iterator& rhv) const; //O(1)
        bool operator<=(const const_iterator& rhv) const; //O(1)
        bool operator>(const const_iterator& rhv) const; //O(1)
        bool operator>=(const const_iterator& rhv) const; //O(1)
    protected:
        explicit const_iterator(pointer ptr); //O(1)
    private:
        pointer ptr_;
    };

public:
    class iterator : public const_iterator {
        friend Vector<value_type>;
    public:
        iterator(); //O(1)
        iterator(const iterator& rhv); //O(1)
        ~iterator(); //O(1)
        value_type& operator*(); //O(1)
        value_type* operator->(); //O(1)
    protected:
        explicit iterator(pointer ptr); //O(1)
    };

public:
    class const_reverse_iterator {
        friend Vector<value_type>;
    public:
        const_reverse_iterator(); //O(1)
        const_reverse_iterator(const const_reverse_iterator& rhv); //O(1)
        ~const_reverse_iterator(); //O(1)
        const const_reverse_iterator& operator=(const const_reverse_iterator& rhv); //O(1)
        const value_type& operator*() const; //O(1)
        const value_type* operator->() const; //O(1)
        
        const const_reverse_iterator& operator++(); //O(1)
        const const_reverse_iterator operator++(value_type); //O(1)
        const const_reverse_iterator& operator--(); //O(1)
        const const_reverse_iterator operator--(value_type); //O(1)
        const const_reverse_iterator operator+=(const size_type i); //O(1)
        const const_reverse_iterator operator-=(const size_type i); //O(1)
        const const_reverse_iterator operator+(const size_type i) const; //O(1)
        const const_reverse_iterator operator-(const size_type i) const; //O(1)
        bool operator==(const const_reverse_iterator& rhv) const; //O(1)
        bool operator!=(const const_reverse_iterator& rhv) const; //O(1)
        bool operator<(const const_reverse_iterator& rhv) const; //O(1)
        bool operator<=(const const_reverse_iterator& rhv) const; //O(1)
        bool operator>(const const_reverse_iterator& rhv) const; //O(1)
        bool operator>=(const const_reverse_iterator& rhv) const; //O(1)
    protected:
        explicit const_reverse_iterator(pointer ptr); //O(1)
    private:
        pointer ptr_;
    };
public:
    class reverse_iterator : public const_reverse_iterator {
        friend Vector<value_type>;
    public:
        reverse_iterator(); //O(1)
        reverse_iterator(const reverse_iterator& rhv); //O(1)
        ~reverse_iterator(); //O(1)
        value_type& operator*(); //O(1)
        value_type* operator->(); //O(1)
    protected:
        explicit reverse_iterator(pointer ptr); //O(1)
    };

public:
    Vector(); //O(1)
    Vector(const size_type size); //O(1)
    Vector(const int size, const_reference init); //O(n)
    Vector(const Vector<value_type>& rhv); //O(n)
    Vector(Vector<value_type>&& rhv); //O(1)
    template <typename InputIterator> Vector(InputIterator f, InputIterator l); //O(n)
    ~Vector(); //O(1)
    
    void set(const size_type index, const_reference value); //O(1)
    const_reference get(const size_type index) const; //O(1)

    size_type size() const; //O(1)
    size_type max_size() const; //O(1)
    bool empty() const; //O(1)
    void resize(const size_type size, const_reference init = value_type()); //O(n)
    void clear(); //O(n)
    size_type capacity() const; //O(1)
    void reserve(const size_type size); //O(n)

    void push_back(const_reference element); //O(1) //O(n)
    void pop_back(); //O(1)
    const_reference front() const; //O(1)
    reference front(); //O(1)
    const_reference back() const; //O(1)
    reference back(); //O(1)

    const Vector<value_type>& operator=(const Vector<value_type>& rhv); //O(n)
    const Vector<value_type>& operator=(Vector<value_type>&& rhv); //O(1)
    reference operator[](const size_type index); //O(1)
    const_reference operator[](const size_type index) const; //O(1)
    bool operator==(const Vector<value_type>& rhv) const; //O(n)
    bool operator!=(const Vector<value_type>& rhv) const; //O(n)
    bool operator<(const Vector<value_type>& rhv) const; //O(n)
    bool operator<=(const Vector<value_type>& rhv) const; //O(n)
    bool operator>(const Vector<value_type>& rhv) const; //O(n)
    bool operator>=(const Vector<value_type>& rhv) const; //O(n)

    const_iterator begin() const; //O(1)
    iterator begin(); //O(1)
    const_iterator end() const; //O(1)
    iterator end(); //O(1)
    const_reverse_iterator rbegin() const; //O(1)
    reverse_iterator rbegin(); //O(1)
    const_reverse_iterator rend() const; //O(1)
    reverse_iterator rend(); //O(1)

public:
    iterator insert(iterator pos, const T& x);//O(n)
    void insert(iterator pos, const int n, const T& x); //O(n)
    template <typename InputIterator>
    void insert(iterator pos, InputIterator f, InputIterator l); //O(n)
    
    iterator erase(iterator pos); //O(n)
    iterator erase(iterator f, iterator l); //O(n)

private:
    pointer begin_;
    pointer end_;
    pointer bufferEnd_;
};

}

#include "Vector.cpp"
#endif /// _VECTOR_HPP__
