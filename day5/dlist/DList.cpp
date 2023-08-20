#include "DList.hpp"

#include <cassert>
#include <algorithm>
#include <cmath>

namespace vhuk {

template <typename T>
std::ostream&
operator<<(std::ostream& out, const DList<T>& list)
{
    out << "{ ";
    typedef typename DList<T>::size_type size_type;
    const size_type s = list.size();
    typename DList<T>::const_iterator it = list.cbegin();
    for (size_type i = 0; i < s; ++i, ++it) {
        out << *it << " ";
    }
    out << '}';
    return out;
}

template <typename T>
DList<T>::DList()
    : head(NULL)
    , tail(NULL)
{
}


template <typename T>
DList<T>::DList(const size_type size)
    : head(NULL)
    , tail(NULL)
{
    assert(size >= 0 && size <= max_size());
    for (size_type i = 0; i < size; ++i) {
        push_front(value_type());
    }
}

template <typename T>
DList<T>::DList(const int size, const_reference init)
    : head(NULL)
    , tail(NULL)
{
    assert(size >= 0 && static_cast<size_type>(size) <= max_size());
    resize(size, init);
}

template <typename T>
template <typename InputIterator>
DList<T>::DList(InputIterator f, InputIterator l)
    : head(NULL)
    , tail(NULL)
{
    assert(f != NULL && l != NULL);
    for ( ; f != l; ++f) {
        push_back(f.ptr->val);
    }
}

template <typename T>
DList<T>::DList(const DList<T>& rhv)
    : head(NULL)
    , tail(NULL)
{
    if (NULL == rhv.head) {
        return;
    }
    for (const_iterator it = rhv.begin(); it.ptr != rhv.tail->next; ++it) {
        push_back(it.ptr->val);
    }
}

template <typename T>
DList<T>::DList(DList<T>&& rhv)
    : head(rhv.head)
    , tail(rhv.tail)
{
    rhv.head = NULL;
    rhv.tail = NULL;
}

template <typename T>
DList<T>::DList(std::initializer_list<T> init)
    : head(NULL)
    , tail(NULL)
{
    for (auto i : init) {
        push_back(i);
    }
}

template <typename T>
DList<T>::~DList()
{
    clear();
}

template <typename T>
void
DList<T>::swap(DList<value_type>& rhv)
{
    Node* temp = head;
    head = rhv.head;
    rhv.head = temp;
    temp = tail;
    tail = rhv.tail;
    rhv.tail = temp;
}

template <typename T>
typename DList<T>::size_type
DList<T>::size() const
{
    if (NULL == head) {
        return 0;
    }
    size_type size = 0;
    for (const_iterator it = cbegin(); it.ptr != tail->next; ++it, ++size) {
    }
    assert(size <= max_size());
    return size;
}

template <typename T>
typename DList<T>::size_type
DList<T>::max_size() const
{
    return static_cast<size_type>(std::pow(2, sizeof(pointer) * 8) / (sizeof(value_type) + sizeof(head) + sizeof(tail))); /// For list
}

template <typename T>
bool
DList<T>::empty() const
{
    return (NULL == head);
}

template <typename T>
void
DList<T>::resize(const size_type size, const_reference init)
{
    assert(size >= 0 && size <= max_size());
    size_type thisSize = this->size();
    for ( ; size > thisSize; ++thisSize) {
        push_back(init);
    }
    for ( ; size < thisSize; --thisSize) {
        pop_back();
    }
}

template <typename T>
void
DList<T>::clear()
{
    while (head != NULL) {
        pop_front();
    }
}

template <typename T>
void
DList<T>::push_front(const_reference element)
{
    head = new Node(element, head, NULL);
    if (NULL == tail)  {
        tail = head;
        return;
    }
    head->next->prev = head;
}

template <typename T>
void
DList<T>::pop_front()
{
    assert(head != NULL);
    if (head != tail) {
        head = head->next;
        head->prev->~Node();
        return;
    }
    delete head;
    head = tail = NULL;
}

template <typename T>
void
DList<T>::push_back(const_reference element)
{
    tail = new Node(element, NULL, tail);
    (NULL == head) ? head = tail : tail->prev->next = tail;
}

template <typename T>
void
DList<T>::pop_back()
{
    assert(head != NULL);
    if (head != tail) {
        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
        return;
    }
    delete tail;
    head = tail = NULL;
}

template <typename T>
typename DList<T>::const_reference
DList<T>::front() const
{
    assert(head != NULL);
    return head->val;
}

template <typename T>
typename DList<T>::reference
DList<T>::front()
{
    assert(head != NULL);
    return head->val;
}

template <typename T>
typename DList<T>::const_reference
DList<T>::back() const
{
    assert(tail != NULL);
    return tail->val;
}

template <typename T>
typename DList<T>::reference
DList<T>::back()
{
    assert(tail != NULL);
    return tail->val;
}

template <typename T>
const DList<T>&
DList<T>::operator=(const DList<T>& rhv)
{
    size_type thisSize = this->size();
    const size_type rhvSize = rhv.size();
    for ( ; thisSize > rhvSize; --thisSize) {
        pop_back();
    }
    iterator pos = begin();
    const_iterator it = rhv.begin();
    for ( ; it.ptr != NULL && pos.ptr != NULL; ++it, ++pos) {
        *pos = *it;
    }
    for ( ; thisSize < rhvSize; ++thisSize, ++it) {
        push_back(*it);
    }

    return *this;
}

template <typename T>
const DList<T>&
DList<T>::operator=(DList<T>&& rhv)
{
    head = rhv.head;
    tail = rhv.tail;

    rhv.head = NULL;
    rhv.tail = NULL;
    return *this;
}

template <typename T>
bool
DList<T>::operator==(const DList<T>& rhv) const
{
    if (size() == rhv.size()) {
        const_iterator it1 = begin();
        const_iterator it2 = rhv.begin();
        for ( ; it1 != end(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool
DList<T>::operator!=(const DList<T>& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
DList<T>::operator<(const DList<T>& rhv) const
{
    if (size() < rhv.size()) {
        return true;
    }
    if (size() == rhv.size()) {
        const_iterator it1 = begin();
        const_iterator it2 = rhv.begin();
        for ( ; it1.ptr != tail->next; ++it1, ++it2) {
            if (*it1 > *it2) {
                return false;
            }
            if (*it1 < *it2) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool
DList<T>::operator<=(const DList<T>& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
DList<T>::operator>(const DList<T>& rhv) const
{
    return rhv < *this;
}

template <typename T>
bool
DList<T>::operator>=(const DList<T>& rhv) const
{
    return !(*this < rhv);
}

template <typename T>
typename DList<T>::const_iterator
DList<T>::cbegin() const
{
    return const_iterator(head);
}

template <typename T>
typename DList<T>::iterator
DList<T>::begin()
{
    return iterator(head);
}

template <typename T>
typename DList<T>::const_iterator
DList<T>::cend() const
{
    return const_iterator(NULL);
}

template <typename T>
typename DList<T>::iterator
DList<T>::end()
{
    return iterator(NULL);
}

template <typename T>
typename DList<T>::const_reverse_iterator
DList<T>::crbegin() const
{
    return const_raverse_iterator(tail);
}

template <typename T>
typename DList<T>::reverse_iterator
DList<T>::rbegin()
{
    return reverse_iterator(tail);
}

template <typename T>
typename DList<T>::const_reverse_iterator
DList<T>::crend() const
{
    return const_reverse_iterator(NULL);
}

template <typename T>
typename DList<T>::reverse_iterator
DList<T>::rend()
{
    return reverse_iterator(NULL);
}

template <typename T>
typename DList<T>::iterator
DList<T>::insert(iterator pos, const value_type& x)
{
    if (head == pos.ptr) {
        push_front(x);
        return begin();
    }
    --pos;
    pos = insert_after(pos, x);
    return pos;
}

template <typename T>
void
DList<T>::insert(iterator pos, const int n, const value_type& x)
{
    assert( n > 0 && static_cast<size_type>(n) <= max_size() - size());
    for (int i = n ; i > 0; --i) {
        pos = insert(pos, x);
    }
}

template <typename T>
template <typename InputIterator>
void
DList<T>::insert(iterator pos, InputIterator f, InputIterator l)
{
    assert(f != NULL);
    for ( ; f != l; ++f, ++pos) {
        pos = insert(pos, *f);
    }
}

template <typename T>
typename DList<T>::iterator
DList<T>::insert_after(iterator pos, const value_type& x)
{
    assert(pos != NULL);
    Node* temp = new Node(x, pos.ptr->next, pos.ptr);
    pos.ptr->next = temp;
    if (pos.ptr == tail) {
        tail = temp;
        ++pos;
        return pos;
    }
    temp->next->prev = temp;
    iterator it(temp);
    return it;
}

template <typename T>
void
DList<T>::insert_after(iterator pos, const int n, const value_type& x)
{
    assert( n > 0 && static_cast<size_type>(n) <= max_size() - size());
    for (int i = n ; i > 0; --i) {
        pos = insert_after(pos, x);
    }
}

template <typename T>
template <typename InputIterator>
void
DList<T>::insert_after(iterator pos, InputIterator f, InputIterator l)
{
    assert(f != NULL);
    for ( ; f != l; ++f) {
        pos = insert_after(pos, *f);
    }
}

template <typename T>
typename DList<T>::iterator
DList<T>::erase(iterator pos)
{
    assert(pos != NULL);
    if (pos.ptr == head) {
        pop_front();
        return begin();
    }
    --pos;
    pos = erase_after(pos);
    return pos;
}

template <typename T>
typename DList<T>::iterator
DList<T>::erase(iterator f, iterator l)
{
    assert(f != NULL && f != l);
    size_t counter = 0;
    for (iterator it = f; it != l; ++counter, ++it) {}

    while (counter > 0) {
        f = erase(f);
        --counter;
    }
    return f;

}

template <typename T>
typename DList<T>::iterator
DList<T>::erase_after(iterator pos)
{
    assert(pos != NULL && pos.ptr != tail);
    pos.ptr->next = pos.ptr->next->next;
    if (pos.ptr == tail->prev) {
        delete tail;
        tail = pos.ptr;
        tail->next = NULL;
        return pos;
    }
    delete pos.ptr->next->prev;
    pos.ptr->next->prev = pos.ptr;

    return pos;
}

template <typename T>
void
DList<T>::splice(iterator pos, DList<value_type>& rhv)
{
    assert(pos != NULL);
    rhv.tail->next = pos.ptr;
    if (pos.ptr == head) {
        head = rhv.head;
    } else {
        pos.ptr->prev->next = rhv.head;
        rhv.head->prev = pos.ptr->prev;
    }
    pos.ptr->prev = rhv.tail;
    rhv.tail = rhv.head = NULL;
}


template <typename T>
void
DList<T>::splice(iterator pos, DList<value_type>& rhv, iterator i)
{
    assert(i != NULL);
    insert(pos, *i);
    rhv.erase(i);
}

template <typename T>
void
DList<T>::splice(iterator pos, DList<value_type>& rhv, iterator f, iterator l)
{
    assert(f != NULL && l != NULL && f != l);
    insert(pos, f, l);
    rhv.erase(f, l);
}

/// const_iterator implementation /////////////////////////////////////

template <typename T>
DList<T>::const_iterator::const_iterator(Node* ptr)
    : ptr(ptr)
{
}

template <typename T>
DList<T>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr(rhv.ptr)
{
}

template <typename T>
DList<T>::const_iterator::~const_iterator()
{
    ptr = NULL;
}

template <typename T>
const typename DList<T>::const_iterator&
DList<T>::const_iterator::operator=(const const_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const T&
DList<T>::const_iterator::operator*() const
{
    assert(ptr != NULL);
    return ptr->val;
}

template <typename T>
const T*
DList<T>::const_iterator::operator->() const
{
    assert(ptr != NULL);
    return ptr;
}

template <typename T>
const typename DList<T>::const_iterator
DList<T>::const_iterator::operator++()
{
    ptr = ptr->next;
    return ptr;
}

template <typename T>
const typename DList<T>::const_iterator
DList<T>::const_iterator::operator++(value_type)
{
    ptr = ptr->next;
    return ptr;
}

template <typename T>
const typename DList<T>::const_iterator
DList<T>::const_iterator::operator--()
{
    ptr = ptr->prev;
    return ptr;
}

template <typename T>
const typename DList<T>::const_iterator
DList<T>::const_iterator::operator--(value_type)
{
    ptr = ptr->prev;
    return ptr;
}

template <typename T>
bool
DList<T>::const_iterator::operator==(const const_iterator& rhv) const
{
    return this->ptr == rhv.ptr;
}

template <typename T>
bool
DList<T>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return this->ptr != rhv.ptr;
}

/// iterator implementation /////////////////////////////////////

template <typename T>
DList<T>::iterator::iterator(Node* ptr)
    : const_iterator(ptr)
{
}

template <typename T>
DList<T>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv.ptr)
{
}

template <typename T>
DList<T>::iterator::~iterator()
{
    const_iterator::ptr = NULL;
}

template <typename T>
T&
DList<T>::iterator::operator*()
{
    assert(const_iterator::ptr != NULL);
    return const_iterator::ptr->val;
}

template <typename T>
T*
DList<T>::iterator::operator->()
{
    assert(const_iterator::ptr != NULL);
    return const_iterator::ptr;
}

template <typename T>
const typename DList<T>::iterator&
DList<T>::iterator::operator=(const iterator& rhv)
{
    const_iterator::ptr = rhv.ptr;
    return *this;
}

template <typename T>
bool
DList<T>::iterator::operator==(const iterator& rhv) const
{
    return const_iterator::ptr == rhv.ptr;
}

template <typename T>
bool
DList<T>::iterator::operator!=(const iterator& rhv) const
{
    return const_iterator::ptr != rhv.ptr;
}

/// const_reverse_iterator implementation /////////////////////////////////////

template <typename T>
DList<T>::const_reverse_iterator::const_reverse_iterator(Node* ptr)
    : ptr(ptr)
{
}

template <typename T>
DList<T>::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator& rhv)
    : ptr(rhv.ptr)
{
}

template <typename T>
DList<T>::const_reverse_iterator::~const_reverse_iterator()
{
    ptr = NULL;
}

template <typename T>
const typename DList<T>::const_reverse_iterator&
DList<T>::const_reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const T&
DList<T>::const_reverse_iterator::operator*() const
{
    assert(ptr != NULL);
    return ptr->val;
}

template <typename T>
const T*
DList<T>::const_reverse_iterator::operator->() const
{
    assert(ptr != NULL);
    return ptr;
}

template <typename T>
const typename DList<T>::const_reverse_iterator
DList<T>::const_reverse_iterator::operator++()
{
    ptr = ptr->prev;
    return ptr;
}

template <typename T>
const typename DList<T>::const_reverse_iterator
DList<T>::const_reverse_iterator::operator++(value_type)
{
    ptr = ptr->prev;
    return ptr;
}

template <typename T>
const typename DList<T>::const_reverse_iterator
DList<T>::const_reverse_iterator::operator--()
{
    ptr = ptr->next;
    return ptr;
}

template <typename T>
const typename DList<T>::const_reverse_iterator
DList<T>::const_reverse_iterator::operator--(value_type)
{
    ptr = ptr->next;
    return ptr;
}

template <typename T>
bool
DList<T>::const_reverse_iterator::operator==(const const_reverse_iterator& rhv) const
{
    return this->ptr == rhv.ptr;
}

template <typename T>
bool
DList<T>::const_reverse_iterator::operator!=(const const_reverse_iterator& rhv) const
{
    return this->ptr != rhv.ptr;
}

/// reverse_iterator implementation /////////////////////////////////////

template <typename T>
DList<T>::reverse_iterator::reverse_iterator(Node* ptr)
    : const_reverse_iterator(ptr)
{
}

template <typename T>
DList<T>::reverse_iterator::reverse_iterator(const reverse_iterator& rhv)
    : const_reverse_iterator(rhv.ptr)
{
}

template <typename T>
DList<T>::reverse_iterator::~reverse_iterator()
{
    const_reverse_iterator::ptr = NULL;
}

template <typename T>
T&
DList<T>::reverse_iterator::operator*()
{
    assert(const_reverse_iterator::ptr != NULL);
    return const_reverse_iterator::ptr->val;
}

template <typename T>
T*
DList<T>::reverse_iterator::operator->()
{
    assert(const_reverse_iterator::ptr != NULL);
    return const_reverse_iterator::ptr;
}

template <typename T>
const typename DList<T>::reverse_iterator&
DList<T>::reverse_iterator::operator=(const reverse_iterator& rhv)
{
    const_reverse_iterator::ptr = rhv.ptr;
    return *this;
}

template <typename T>
bool
DList<T>::reverse_iterator::operator==(const reverse_iterator& rhv) const
{
    return const_reverse_iterator::ptr == rhv.ptr;
}

template <typename T>
bool
DList<T>::reverse_iterator::operator!=(const reverse_iterator& rhv) const
{
    return const_reverse_iterator::ptr != rhv.ptr;
}


}

