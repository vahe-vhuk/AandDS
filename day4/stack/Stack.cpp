#include <cassert>
#include "Stack.hpp"

namespace vhuk {

template <typename T, typename Sequence>
bool
operator==(const Stack<T, Sequence>& lhv, const Stack<T, Sequence>& rhv)
{
    if (lhv.size() != rhv.size()) {
        return false;
    }
    typedef typename Sequence::const_iterator const_iterator;
    const_iterator it1 = rhv.begin();
    const_iterator it2 = lhv.begin();
    for ( ; it1 != rhv.end(); ++it1, ++it2) {
        if (*it1 != *it2) {
            return false;
        }
    }
    return true;
}

template <typename T, typename Sequence>
bool
operator<(const Stack<T, Sequence>& lhv, const Stack<T, Sequence>& rhv)
{
    if (lhv.size() == rhv.size()) {
        typedef typename Sequence::const_iterator const_iterator;
        const_iterator it1 = rhv.begin();
        const_iterator it2 = lhv.begin();
        for ( ; it1 != rhv.end(); ++it1, ++it2) {
            if (*it1 > *it2) {
                return false;
            }
        }
    }
    return lhv.size() < rhv.size();
}

template <typename T, typename Sequence>
bool
operator>(const Stack<T, Sequence>& lhv, const Stack<T, Sequence>& rhv)
{
    return !(lhv < rhv || lhv == rhv); 
}

template <typename T, typename Sequence>
bool
operator<=(const Stack<T, Sequence>& lhv, const Stack<T, Sequence>& rhv)
{
    return !(lhv > rhv); 
}

template <typename T, typename Sequence>
bool
operator>=(const Stack<T, Sequence>& lhv, const Stack<T, Sequence>& rhv)
{
    return !(lhv < rhv); 
}

template <typename T, typename Sequence>
Stack<T, Sequence>::Stack()
    : Sequence()
{
}

template <typename T, typename Sequence>
Stack<T, Sequence>::Stack(const Stack& rhv)
    : Sequence(rhv)
{
}

template <typename T, typename Sequence>
Stack<T, Sequence>&
Stack<T, Sequence>::operator=(const Stack& rhv)
{
    Sequence::operator=(rhv);
    return *this;
}

template <typename T, typename Sequence>
bool
Stack<T, Sequence>::empty() const
{
    return Sequence::empty();
}

template <typename T, typename Sequence>
typename Stack<T, Sequence>::size_type
Stack<T, Sequence>::size() const
{
    return Sequence::size();
}

template <typename T, typename Sequence>
typename Stack<T, Sequence>::value_type&
Stack<T, Sequence>::top()
{
    assert(!empty());
    return Sequence::back();
}

template <typename T, typename Sequence>
const typename Stack<T, Sequence>::value_type&
Stack<T, Sequence>::top() const
{
    assert(!empty());
    return Sequence::back();
}

template <typename T, typename Sequence>
void
Stack<T, Sequence>::push(const value_type& d)
{
    return Sequence::push_back(d);
}

template <typename T, typename Sequence>
void
Stack<T, Sequence>::pop()
{
    assert(!empty());
    return Sequence::pop_back();
}

}
