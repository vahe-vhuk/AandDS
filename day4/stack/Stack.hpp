#ifndef _STACK_HPP__
#define _STACK_HPP__

#include "../vector/Vector.hpp"

namespace vhuk {

template <typename T, typename Sequence = vhuk::Vector<T> >
class Stack : private Sequence
{
    template <typename T2, typename Sequence2>
    friend bool operator==(const Stack<T2, Sequence2>& lhv, const Stack<T2, Sequence2>& rhv); //O(n)
    template <typename T2, typename Sequence2>
    friend bool operator<(const Stack<T2, Sequence2>& lhv, const Stack<T2, Sequence2>& rhv); //O(n)
    template <typename T2, typename Sequence2>
    friend bool operator>(const Stack<T2, Sequence2>& lhv, const Stack<T2, Sequence2>& rhv); //O(n)
    template <typename T2, typename Sequence2>
    friend bool operator<=(const Stack<T2, Sequence2>& lhv, const Stack<T2, Sequence2>& rhv); //O(n)
    template <typename T2, typename Sequence2>
    friend bool operator>=(const Stack<T2, Sequence2>& lhv, const Stack<T2, Sequence2>& rhv); //O(n)

public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;

public:
    Stack(); //O(1)
    Stack(const Stack& rhv); //O(n)
    Stack& operator=(const Stack& rhv); //O(n)
    bool empty() const; //O(1)
    size_type size() const; //O(1)
    value_type& top(); //O(1)
    const value_type& top() const; //O(1)
    void push(const value_type& d); //O(1) //O(n)
    void pop(); //O(1)
};

}

#include "Stack.cpp"

#endif /// _STACK_HPP__
