#include "List.hpp"

#include <cassert>
#include <algorithm>
#include <cmath>

namespace vhuk {

template <typename T>
std::ostream&
operator<<(std::ostream& out, const List<T>& list)
{
    out << "{ ";
    typedef typename List<T>::size_type size_type;
    const size_type s = list.size();
    typename List<T>::const_iterator it = list.cbegin();
    for (size_type i = 0; i < s; ++i, ++it) {
        out << *it << " ";
    }
    out << '}';
    return out;
}

template <typename T>
List<T>::List()
    : head(NULL)
    , tail(NULL)
{
}


template <typename T>
List<T>::List(const size_type size)
    : head(NULL)
    , tail(NULL)
{
    assert(size >= 0 && size <= max_size());
    for (size_type i = 0; i < size; ++i) {
        push_front(value_type());
    }
}

template <typename T>
List<T>::List(const int size, const_reference init)
    : head(NULL)
    , tail(NULL)
{
    assert(size >= 0 && static_cast<size_type>(size) <= max_size());
    for (int i = 0; i < size; ++i) {
        push_front(init);
    }
}

template <typename T>
template <typename InputIterator>
List<T>::List(InputIterator f, InputIterator l)
    : head(NULL)
    , tail(NULL)
{
    assert(f != NULL && l != NULL);
    for ( ; f != l; ++f) {
        push_back(f.ptr->data_);
    }
}

template <typename T>
List<T>::List(const List<T>& rhv)
    : head(NULL)
    , tail(NULL)
{
    const_iterator it = rhv.begin();
    for ( ; it.ptr != rhv.tail->next; ++it) {
        push_back(it.ptr->data_);
    }
}

template <typename T>
List<T>::List(List<T>&& rhv)
    : head(rhv.head)
    , tail(rhv.tail)
{
    rhv.head = NULL;
    rhv.tail = NULL;
}

template <typename T>
List<T>::List(std::initializer_list<T> init)
    : head(NULL)
    , tail(NULL)
{
    for (auto i : init) {
        push_back(i);
    }
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
void
List<T>::swap(List<value_type>& rhv)
{
    Node* temp = head;
    head = rhv.head;
    rhv.head = temp;
    temp = tail;
    tail = rhv.tail;
    rhv.tail = temp;
}

template <typename T>
typename List<T>::size_type
List<T>::size() const
{
    if (NULL == head) {
        return 0;
    }
    const_iterator it = cbegin();
    size_type size = 0;
    for ( ; it.ptr != tail->next; ++it, ++size) {
    }
    assert(size <= max_size());
    return size;
}

template <typename T>
typename List<T>::size_type
List<T>::max_size() const
{
    return static_cast<size_type>(std::pow(2, sizeof(pointer) * 8) / (sizeof(value_type) + sizeof(head) + sizeof(tail))); /// For single list
}

template <typename T>
bool
List<T>::empty() const
{
    return (NULL == head);
}

template <typename T>
void
List<T>::resize(const size_type size, const_reference init)
{
    assert(size >= 0 && size <= max_size());
    if (0 == size) {
        clear();
    }
    size_type thisSize = this->size();
    while (size > thisSize) {
        push_back(init);
        ++thisSize;
    }
    while (size < thisSize) {
        iterator it(tail);
        erase(it);
        --thisSize;
    }
}

template <typename T>
void
List<T>::clear()
{
    while (head != NULL) {
        pop_front();
    }
}

template <typename T>
void
List<T>::push_front(const_reference element)
{
    head = new Node(element, head);
    if (NULL == tail)  {
        tail = head;
    }
}

template <typename T>
void
List<T>::pop_front()
{
    assert(head != NULL);
    if (head != tail) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    delete head;
    head = tail = NULL;
}

template <typename T>
void
List<T>::push_back(const_reference element)
{
    tail = new Node(element, tail);
    if (NULL == head)  {
        head = tail;
        return;
    }
    tail->next->next = tail;
    tail->next = NULL;

}

template <typename T>
void
List<T>::pop_back()
{
    assert(head != NULL);
    if (!head->next) {
        delete head;
        head = tail = NULL;
    }
    Node* it = head;
    for (; it->next != tail; it = it->next);
    delete it->next;
    it->next = NULL;
    tail = it;
}

template <typename T>
typename List<T>::const_reference
List<T>::front() const
{
    assert(head != NULL);
    return head->data_;
}

template <typename T>
typename List<T>::reference
List<T>::front()
{
    assert(head != NULL);
    return head->data_;
}

template <typename T>
typename List<T>::const_reference
List<T>::back() const
{
    assert(tail != NULL);
    return tail->data_;
}

template <typename T>
typename List<T>::reference
List<T>::back()
{
    assert(tail != NULL);
    return tail->data_;
}

template <typename T>
const List<T>&
List<T>::operator=(const List<T>& rhv)
{
    clear();
    iterator it(rhv->head);
    for ( ; it->next != NULL; ++it) {
        push_back(it->data_);
    }
    return *this;
}

template <typename T>
const List<T>&
List<T>::operator=(List<T>&& rhv)
{
    clear();
    head = rhv.head;
    tail = rhv.tail;

    rhv.head = NULL;
    rhv.tail = NULL;
    return *this;
}

template <typename T>
bool
List<T>::operator==(const List<T>& rhv) const
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
List<T>::operator!=(const List<T>& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
List<T>::operator<(const List<T>& rhv) const
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
List<T>::operator<=(const List<T>& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
List<T>::operator>(const List<T>& rhv) const
{
    return rhv < *this;
}

template <typename T>
bool
List<T>::operator>=(const List<T>& rhv) const
{
    return !(*this < rhv);
}

template <typename T>
typename List<T>::const_iterator
List<T>::cbefore_begin() const
{
    return const_iterator(new Node(0, head));
}

template <typename T>
typename List<T>::iterator
List<T>::before_begin()
{
    return iterator(new Node(0, head));
}

template <typename T>
typename List<T>::const_iterator
List<T>::cbegin() const
{
    return const_iterator(head);
}

template <typename T>
typename List<T>::iterator
List<T>::begin()
{
    return iterator(head);
}

template <typename T>
typename List<T>::const_iterator
List<T>::cend() const
{
    return const_iterator(NULL);
}

template <typename T>
typename List<T>::iterator
List<T>::end()
{
    return iterator(NULL);
}

template <typename T>
typename List<T>::iterator
List<T>::insert(iterator pos, const value_type& x)
{
    if (NULL == head) {
        push_front(x);
        return begin();
    }

    iterator it = insert_after(pos, x);
    if (size() != 1) {
        std::swap(*it, *pos);
    }
    return pos;
}

template <typename T>
void
List<T>::insert(iterator pos, const int n, const value_type& x)
{
    assert( n > 0 && static_cast<size_type>(n) <= max_size() - size());
    for (int i = n ; i > 0; --i) {
        pos = insert(pos, x);
    }
}

template <typename T>
template <typename InputIterator>
void
List<T>::insert(iterator pos, InputIterator f, InputIterator l)
{
    assert(f != NULL);
    for ( ; f != l; ++f, ++pos) {
        pos = insert(pos, *f);
    }
}

template <typename T>
typename List<T>::iterator
List<T>::insert_after(iterator pos, const value_type& x)
{
    assert(pos != NULL);
    if (pos.ptr->next == head) {
        head = new Node(x, head);
        return iterator(head);
    }
    Node* temp = new Node(x, pos.ptr->next);
    pos.ptr->next = temp;
    if (pos.ptr == tail) {
        tail = temp;
    }
    iterator it(temp);
    return it;
}

template <typename T>
void
List<T>::insert_after(iterator pos, const int n, const value_type& x)
{
    assert( n > 0 && static_cast<size_type>(n) <= max_size() - size());
    for (int i = n ; i > 0; --i) {
        pos = insert_after(pos, x);
    }
}

template <typename T>
template <typename InputIterator>
void
List<T>::insert_after(iterator pos, InputIterator f, InputIterator l)
{
    assert(f != NULL);
    for ( ; f != l; ++f) {
        pos = insert_after(pos, *f);
    }
}

template <typename T>
typename List<T>::iterator
List<T>::erase(iterator pos)
{
    assert(pos != NULL);
    if (pos.ptr == head) {
        pop_front();
        return iterator(head);
    }
    if (pos.ptr == tail) {
        iterator it = begin();
        for ( ; it.ptr->next != pos.ptr; ++it) {}
        tail = it.ptr;
        tail->next = NULL;
        delete pos.ptr;
        return iterator(tail);
    }
    std::swap(*pos, pos.ptr->next->data_);
    erase_after(pos);
    return pos;
}

template <typename T>
typename List<T>::iterator
List<T>::erase(iterator f, iterator l)
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
typename List<T>::iterator
List<T>::erase_after(iterator pos)
{
    assert(pos != NULL && pos.ptr != tail);
    Node* temp = pos.ptr->next;
    pos.ptr->next = temp->next;
    if (temp == tail) {
        tail = pos.ptr;
    }
    delete temp;
    return pos;
}

template <typename T>
void
List<T>::splice(iterator pos, List<value_type>& rhv)
{
    assert(pos != NULL);
    iterator it = begin();
    if (pos == begin()) {
        head = rhv.head;
    } else {
        for ( ; it.ptr->next != pos.ptr; ++it) {}
        it.ptr->next = rhv.head;
    }
    rhv.tail->next = pos.ptr;
    rhv.head = NULL;
    rhv.tail = NULL;
}

template <typename T>
void
List<T>::splice(iterator pos, List<value_type>& rhv, iterator i)
{
    assert(i != NULL);
    insert(pos, *i);
    rhv.erase(i);
}

template <typename T>
void
List<T>::splice(iterator pos, List<value_type>& rhv, iterator f, iterator l)
{
    assert(f != NULL && l != NULL && f != l);
    insert(pos, f, l);
    rhv.erase(f, l);
}

/// const_iterator implementation /////////////////////////////////////

template <typename T>
List<T>::const_iterator::const_iterator(Node* ptr)
    : ptr(ptr)
{
}

template <typename T>
List<T>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr(rhv.ptr)
{
}

template <typename T>
List<T>::const_iterator::~const_iterator()
{
    ptr = NULL;
}

template <typename T>
const typename List<T>::const_iterator&
List<T>::const_iterator::operator=(const const_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const T&
List<T>::const_iterator::operator*() const
{
    assert(ptr != NULL);
    return ptr->data_;
}

template <typename T>
const T*
List<T>::const_iterator::operator->() const
{
    assert(ptr != NULL);
    return ptr;
}

template <typename T>
const typename List<T>::const_iterator
List<T>::const_iterator::operator++()
{
    ptr = ptr->next;
    return ptr;
}

template <typename T>
const typename List<T>::const_iterator
List<T>::const_iterator::operator++(value_type)
{
    ptr = ptr->next;
    return ptr;
}

template <typename T>
bool
List<T>::const_iterator::operator==(const const_iterator& rhv) const
{
    return this->ptr == rhv.ptr;
}

template <typename T>
bool
List<T>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return this->ptr != rhv.ptr;
}

/// iterator implementation /////////////////////////////////////

template <typename T>
List<T>::iterator::iterator(Node* ptr)
    : const_iterator(ptr)
{
}

template <typename T>
List<T>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv.ptr)
{
}

template <typename T>
List<T>::iterator::~iterator()
{
    const_iterator::ptr = NULL;
}

template <typename T>
T&
List<T>::iterator::operator*()
{
    assert(const_iterator::ptr != NULL);
    return const_iterator::ptr->data_;
}

template <typename T>
T*
List<T>::iterator::operator->()
{
    assert(const_iterator::ptr != NULL);
    return const_iterator::ptr;
}

template <typename T>
const typename List<T>::iterator&
List<T>::iterator::operator=(const iterator& rhv)
{
    const_iterator::ptr = rhv.ptr;
    return *this;
}

template <typename T>
bool
List<T>::iterator::operator==(const iterator& rhv) const
{
    return const_iterator::ptr == rhv.ptr;
}

template <typename T>
bool
List<T>::iterator::operator!=(const iterator& rhv) const
{
    return const_iterator::ptr != rhv.ptr;
}


}

