#ifndef _DLIST_HPP__
#define _DLIST_HPP__

#include <iostream>

namespace vhuk {

template <typename T> class DList;

template <typename T>
std::istream& operator>>(std::istream& in, DList<T>& v);

template <typename T>
std::ostream& operator<<(std::ostream& out, const DList<T>& v);

template <typename T>
class DList
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
        Node() {};
        Node(const_reference d = 0, Node* n = NULL, Node* p = NULL)
            : val(d), next(n), prev(p) {}
        value_type val;
        Node* next;
        Node* prev;
    };

public:
    class const_iterator {
        friend DList<value_type>;
    public:
        const_iterator(const const_iterator& rhv);
        ~const_iterator();
        const const_iterator& operator=(const const_iterator& rhv);
        const value_type& operator*() const;
        const value_type* operator->() const;
        
        const const_iterator operator++();
        const const_iterator operator++(value_type);
        const const_iterator operator--();
        const const_iterator operator--(value_type);
        bool operator==(const const_iterator& rhv) const;
        bool operator!=(const const_iterator& rhv) const;
    private:
        const_iterator(Node* ptr = NULL);
    private:
        Node* ptr;
    };

public:
    class iterator : public const_iterator {
    public:
        iterator(Node* ptr = NULL);
        iterator(const iterator& rhv);
        ~iterator();
        value_type& operator*();
        value_type* operator->();
        const iterator& operator=(const iterator& rhv);
        bool operator==(const iterator& rhv) const;
        bool operator!=(const iterator& rhv) const;
    };

public:
    class const_reverse_iterator {
        friend DList<value_type>;
    public:
        const_reverse_iterator(const const_reverse_iterator& rhv);
        ~const_reverse_iterator();
        const const_reverse_iterator& operator=(const const_reverse_iterator& rhv);
        const value_type& operator*() const;
        const value_type* operator->() const;
        
        const const_reverse_iterator operator++();
        const const_reverse_iterator operator++(value_type);
        const const_reverse_iterator operator--();
        const const_reverse_iterator operator--(value_type);
        bool operator==(const const_reverse_iterator& rhv) const;
        bool operator!=(const const_reverse_iterator& rhv) const;
    private:
        const_reverse_iterator(Node* ptr = NULL);
    private:
        Node* ptr;
    };

public:
    class reverse_iterator : public const_reverse_iterator {
    public:
        reverse_iterator(Node* ptr = NULL);
        reverse_iterator(const reverse_iterator& rhv);
        ~reverse_iterator();
        value_type& operator*();
        value_type* operator->();
        const reverse_iterator& operator=(const reverse_iterator& rhv);
        bool operator==(const reverse_iterator& rhv) const;
        bool operator!=(const reverse_iterator& rhv) const;
    };

public:
    DList();
    DList(const size_type size);
    DList(const int size, const_reference init = value_type());
    DList(const DList<value_type>& rhv);
    DList(DList<value_type>&& rhv);
    DList(std::initializer_list<value_type> init);
    template <typename InputIterator>
    DList(InputIterator f, InputIterator l);
    ~DList();
    
    void swap(DList<value_type>& rhv);

    size_type size() const;
    size_type max_size() const;
    bool empty() const;
    void resize(const size_type size, const_reference init = value_type());
    void clear();

    void push_front(const_reference element);
    void pop_front();
    void push_back(const_reference element);
    void pop_back();
    const_reference front() const;
    reference front();
    const_reference back() const;
    reference back();

    const DList<value_type>& operator=(const DList<value_type>& rhv);
    const DList<value_type>& operator=(DList<value_type>&& rhv);
    bool operator==(const DList<value_type>& rhv) const;
    bool operator!=(const DList<value_type>& rhv) const;
    bool operator<(const DList<value_type>& rhv) const;
    bool operator<=(const DList<value_type>& rhv) const;
    bool operator>(const DList<value_type>& rhv) const;
    bool operator>=(const DList<value_type>& rhv) const;

    const_iterator cbegin() const;
    iterator begin();
    const_iterator cend() const;
    iterator end();
    const_reverse_iterator crbegin() const;
    reverse_iterator rbegin();
    const_reverse_iterator crend() const;
    reverse_iterator rend();

public:
    iterator insert(iterator pos, const value_type& x);
    void insert(iterator pos, const int n, const T& x);
    template <typename InputIterator>
    void insert(iterator pos, InputIterator f, InputIterator l);
    iterator insert_after(iterator pos);
    iterator insert_after(iterator pos, const value_type& x);
    void insert_after(iterator pos, const int n, const value_type& x);
    template <typename InputIterator>
    void insert_after(iterator pos, InputIterator f, InputIterator l);

    iterator erase(iterator pos);
    iterator erase(iterator f, iterator l);
    iterator erase_after(iterator pos);

    void splice(iterator pos, DList<value_type>& rhv);
    void splice(iterator pos, DList<value_type>& rhv, iterator i);
    void splice(iterator pos, DList<value_type>& rhv, iterator f, iterator l);

private:
    Node* head;
    Node* tail;
};

}

#include "DList.cpp"

#endif /// _DLIST_HPP__



