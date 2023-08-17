#ifndef _QUEUE_HPP__
#define _QUEUE_HPP__

#include "../vector/Vector.hpp"

namespace vhuk {

template <typename T, typename Sequence = Vector<T> >
class Queue : private Sequence
{
    template <typename T2, typename Sequence2>
    friend bool operator==(const Queue<T2, Sequence2>& lhv, const Queue<T2, Sequence2>& rhv); //O(n)
    template <typename T2, typename Sequence2>
    friend bool operator<(const Queue<T2, Sequence2>& lhv, const Queue<T2, Sequence2>& rhv); //O(n)
    template <typename T2, typename Sequence2>
    friend bool operator>(const Queue<T2, Sequence2>& lhv, const Queue<T2, Sequence2>& rhv); //O(n)
    template <typename T2, typename Sequence2>
    friend bool operator<=(const Queue<T2, Sequence2>& lhv, const Queue<T2, Sequence2>& rhv); //O(n)
    template <typename T2, typename Sequence2>
    friend bool operator>=(const Queue<T2, Sequence2>& lhv, const Queue<T2, Sequence2>& rhv); //O(n)

public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;

public:
    Queue(); //O(1)
    Queue(const Queue& rhv); //O(n)
    Queue& operator=(const Queue& rhv); //O(n)
    bool empty() const; //O(1)
    size_type size() const; //O(1)
    value_type& top(); //O(1)
    const value_type& top() const; //O(1)
    void push(const value_type& d); //O(1) //O(n)
    void pop(); //O(1)
};

}

#include "Queue.cpp"

#endif /// _QUEUE_HPP__
