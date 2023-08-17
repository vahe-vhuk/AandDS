#include <cassert>
#include "Queue.hpp"

namespace vhuk {

template <typename T, typename Sequence>
bool
operator==(const Queue<T, Sequence>& lhv, const Queue<T, Sequence>& rhv)
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
operator<(const Queue<T, Sequence>& lhv, const Queue<T, Sequence>& rhv)
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
operator>(const Queue<T, Sequence>& lhv, const Queue<T, Sequence>& rhv)
{
    return !(lhv < rhv || lhv == rhv); 
}

template <typename T, typename Sequence>
bool
operator<=(const Queue<T, Sequence>& lhv, const Queue<T, Sequence>& rhv)
{
    return !(lhv > rhv); 
}

template <typename T, typename Sequence>
bool
operator>=(const Queue<T, Sequence>& lhv, const Queue<T, Sequence>& rhv)
{
    return !(lhv < rhv); 
}

template <typename T, typename Sequence>
Queue<T, Sequence>::Queue()
    : Sequence()
{
}

template <typename T, typename Sequence>
Queue<T, Sequence>::Queue(const Queue& rhv)
    : Sequence(rhv)
{
}

template <typename T, typename Sequence>
Queue<T, Sequence>&
Queue<T, Sequence>::operator=(const Queue& rhv)
{
    Sequence::operator=(rhv);
    return *this;
}

template <typename T, typename Sequence>
bool
Queue<T, Sequence>::empty() const
{
    return Sequence::empty();
}

template <typename T, typename Sequence>
typename Queue<T, Sequence>::size_type
Queue<T, Sequence>::size() const
{
    return Sequence::size();
}

template <typename T, typename Sequence>
typename Queue<T, Sequence>::value_type&
Queue<T, Sequence>::top()
{
    assert(!empty());
    return Sequence::front();
}

template <typename T, typename Sequence>
const typename Queue<T, Sequence>::value_type&
Queue<T, Sequence>::top() const
{
    assert(!empty());
    return Sequence::front();
}

template <typename T, typename Sequence>
void
Queue<T, Sequence>::push(const value_type& d)
{
    return Sequence::push_back(d);
}

template <typename T, typename Sequence>
void
Queue<T, Sequence>::pop()
{
    assert(!empty());
    Sequence::erase(Sequence::begin());
}

}
