#ifndef _LIST_HPP__
#define _LIST_HPP__

#include <iostream>
#include <initializer_list>

namespace vhuk {

template <typename T> class List;

template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& v);

template <typename T>
class List
{
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

private:
    struct Node {
        Node() {}; //O(1)
        Node(const_reference d = 0, Node* n = NULL) //O(1)
            : data_(d), next(n) {}
        value_type data_;
        Node* next;
    };

public:
    class const_iterator {
        friend List<value_type>;
    public:
        const_iterator(const const_iterator& rhv); //O(1)
        ~const_iterator(); //O(1)
        const const_iterator& operator=(const const_iterator& rhv); //O(1)
        const value_type& operator*() const; //O(1)
        const value_type* operator->() const; //O(1)
        
        const const_iterator operator++(); //O(1)
        const const_iterator operator++(value_type); //O(1)
        bool operator==(const const_iterator& rhv) const; //O(1)
        bool operator!=(const const_iterator& rhv) const; //O(1)
    private:
        const_iterator(Node* ptr = NULL); //O(1)
    private:
        Node* ptr;
    };

public:
    class iterator : public const_iterator { //O(1)
    public:
        iterator(Node* ptr = NULL); //O(1)
        iterator(const iterator& rhv); //O(1)
        ~iterator(); //O(1)
        value_type& operator*(); //O(1)
        value_type* operator->(); //O(1)
        const iterator& operator=(const iterator& rhv); //O(1)
        bool operator==(const iterator& rhv) const; //O(1)
        bool operator!=(const iterator& rhv) const; //O(1)
    };

public:
    List(); //O(1)
    List(const size_type size); //O(n)
    List(const int size, const_reference init = value_type()); //O(n)
    List(const List<value_type>& rhv); //O(n)
    List(List<T>&& rhv); //O(1)
    List(std::initializer_list<value_type> init); //O(n)
    template <typename InputIterator>
    List(InputIterator f, InputIterator l); //O(n)
    ~List(); //O(n)
    
    void swap(List<value_type>& rhv); //O(1)

    size_type size() const; //O(n)
    size_type max_size() const; //O(1)
    bool empty() const; //O(1)
    void resize(const size_type size, const_reference init = value_type()); //O(n) //O(1)
    void clear(); //O(n)

    void push_front(const_reference element); //O(1)
    void pop_front(); //O(1)
    void push_back(const_reference element); //O(1)
    void pop_back(); //O(n)
    const_reference front() const; //O(1)
    reference front(); //O(1)
    const_reference back() const; //O(1)
    reference back(); //O(1)

    const List<value_type>& operator=(const List<value_type>& rhv); //O(n)
    const List<value_type>& operator=(List<value_type>&& rhv); //O(n)
    bool operator==(const List<value_type>& rhv) const; //O(n)
    bool operator!=(const List<value_type>& rhv) const; //O(n)
    bool operator<(const List<value_type>& rhv) const; //O(n)
    bool operator<=(const List<value_type>& rhv) const; //O(n)
    bool operator>(const List<value_type>& rhv) const; //O(n)
    bool operator>=(const List<value_type>& rhv) const; //O(n)

    const_iterator cbefore_begin() const; //O(1)
    iterator before_begin(); //O(1)
    const_iterator cbegin() const; //O(1)
    iterator begin(); //O(1)
    const_iterator cend() const; //O(1)
    iterator end(); //O(1)

public:
    iterator insert(iterator pos, const value_type& x); //O(n)
    void insert(iterator pos, const int n, const T& x); //O(n)
    template <typename InputIterator>
    void insert(iterator pos, InputIterator f, InputIterator l); //O(n)
    iterator insert_after(iterator pos); //O(1)
    iterator insert_after(iterator pos, const value_type& x); //O(1)
    void insert_after(iterator pos, const int n, const value_type& x); //O(n)
    template <typename InputIterator> 
    void insert_after(iterator pos, InputIterator f, InputIterator l); //O(n)

    iterator erase(iterator pos); //O(n)
    iterator erase(iterator f, iterator l); //O(n)
    iterator erase_after(iterator pos); //O(1)

    void splice(iterator pos, List<value_type>& rhv); //O(n)
    void splice(iterator pos, List<value_type>& rhv, iterator i); //O(n)
    void splice(iterator pos, List<value_type>& rhv, iterator f, iterator l); //O(n)

private:
    Node* head;
    Node* tail;
};

}

#include "List.cpp"

#endif /// _LIST_HPP__



