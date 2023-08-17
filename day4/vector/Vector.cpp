#include "Vector.hpp"
#include <climits>
#include <cassert>
#include <algorithm>

namespace vhuk {

const static double RESERVE_COEFF = 2;

template <typename T>
std::ostream&
operator<<(std::ostream& out, const Vector<T>& v)
{
    out << "{ ";
    const size_t s = v.size();
    for (size_t i = 0; i < s; ++i) {
        out << v[i] << ' ';
    }
    out << '}';
    return out;
}

template <typename T>
Vector<T>::Vector()
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
}


template <typename T>
Vector<T>::Vector(const size_type size)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    resize(size);
}

template <typename T>
Vector<T>::Vector(const int size, const_reference init)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    resize(size, init);
}

template <typename T>
template <typename InputIterator>
Vector<T>::Vector(InputIterator f, InputIterator l)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    insert(begin_, f, l);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhv)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    reserve(rhv.capacity());
    const size_type s = rhv.size();
    for (size_t i = 0; i < s; ++i) {
        begin_[i] = rhv[i];
    }
    end_ = begin_ + s;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& rhv)
    : begin_(rhv.begin_)
    , end_(rhv.end_)
    , bufferEnd_(rhv.bufferEnd_)
{
    rhv.begin_ = NULL;
    rhv.end_ = NULL;
    rhv.bufferEnd_ = NULL;
}

template <typename T>
Vector<T>::~Vector()
{
    if (begin_ != NULL) {
        ::operator delete[](begin_);
        begin_ = end_ = bufferEnd_ = NULL;
    }
}

template <typename T>
void
Vector<T>::set(const size_type index, const_reference value)
{
    assert(index < size());
    begin_[index] = value;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::get(const size_type index) const
{
    assert(index < size());
    return begin_[index];
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::size() const
{
    return end_ - begin_;
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::max_size() const
{
    return LLONG_MAX / sizeof(value_type);
}

template <typename T>
bool
Vector<T>::empty() const
{
    return begin_ == end_;
}

template <typename T>
void
Vector<T>::resize(const size_type size, const_reference init)
{
    reserve(size);
    while (size != this->size()) { 
        (size < this->size()) ? pop_back() : push_back(init);
    }
}

template <typename T>
void
Vector<T>::clear()
{
    while (end_ != begin_) {
        this->pop_back();
    }
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::capacity() const
{
    return bufferEnd_ - begin_;
}

template <typename T>
void
Vector<T>::reserve(const size_type size)
{
    if (this->capacity() < size) {
        value_type* temp = reinterpret_cast<value_type*>(::operator new(size * sizeof(T)));
        const size_t s = this->size();
        for (size_t i= 0; i < s; ++i) {
            temp[i] = begin_[i];
        }
        if (begin_ != NULL) {
            ::operator delete[](begin_);
            begin_ = end_ = bufferEnd_ = NULL;
        }
        begin_ = temp;
        end_ = begin_ + s;
        bufferEnd_ = begin_ + size;
    }
}

template <typename T>
void
Vector<T>::push_back(const_reference element)
{
    if (end_ == bufferEnd_) {
        reserve(static_cast<size_type>(RESERVE_COEFF * capacity()));
        reserve(this->size() + 1);
    }
    *end_ = element;
    ++end_;
}

template <typename T>
void
Vector<T>::pop_back()
{
    assert(begin_ != NULL);
    --end_;
    end_->~value_type();
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::front() const
{
    assert(begin_ != NULL);
    return *begin_;
}

template <typename T>
typename Vector<T>::reference
Vector<T>::front()
{
    assert(begin_ != NULL);
    return *begin_;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::back() const
{
    assert(end_ != NULL);
    return *(end_ -1);
}

template <typename T>
typename Vector<T>::reference
Vector<T>::back()
{
    assert(end_ != NULL);
    return *(end_ - 1);
}

template <typename T>
const Vector<T>&
Vector<T>::operator=(const Vector<T>& rhv)
{
    if (this == &rhv) {
        return *this;
    }
    const size_type c = rhv.capacity();
    if (this->capacity() != c) {
        this->~Vector();
    }
    end_ = begin_;
    
    for (size_t i = 0; i < rhv.size(); ++i) {
        this->push_back(rhv[i]);
    }
    return *this;
}

template <typename T>
const Vector<T>&
Vector<T>::operator=(Vector<T>&& rhv)
{
    this->begin_ = rhv.begin_;
    this->end = rhv.end;
    this->bufferEnd_ = rhv.bufferEnd_;

    rhv.begin_ = NULL;
    rhv.end = NULL;
    rhv.bufferEnd_ = NULL;
    return *this;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::operator[](const size_type index) const
{
    assert(index < size());
    return begin_[index];
}

template <typename T>
typename Vector<T>::reference
Vector<T>::operator[](const size_type index)
{
    assert(index < size());
    return begin_[index];
}

template <typename T>
bool
Vector<T>::operator==(const Vector<T>& rhv) const
{
    if (this->size() == rhv.size()) {
        for (size_t i = 0; i < this->size(); ++i) {
            if (begin_[i] != rhv[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool
Vector<T>::operator!=(const Vector<T>& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
Vector<T>::operator<(const Vector<T>& rhv) const
{
    if (this->size() < rhv.size()) {
        return true;
    }

    if (this->size() == rhv.size()) {
        for (size_t i = 0; i < this->size(); ++i) {
            if (begin_[i] < rhv[i]) {
                return true;
            }
            if (begin_[i] > rhv[i]) {
                return false;
            }
        }
    }
    return false;
}

template <typename T>
bool
Vector<T>::operator<=(const Vector<T>& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
Vector<T>::operator>(const Vector<T>& rhv) const
{
    return (rhv < *this);
}

template <typename T>
bool
Vector<T>::operator>=(const Vector<T>& rhv) const
{
    return !(*this < rhv);
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::begin() const
{
    return const_iterator(begin_);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::begin()
{
    return iterator(begin_);
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::end() const
{
    return const_iterator(end_);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::end()
{
    return iterator(end_);
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::rbegin() const
{
    return const_reverse_iterator(end_ - 1);
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::rbegin()
{
    return reverse_iterator(end_ - 1);
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::rend() const
{
    return const_reverse_iterator(begin_ - 1);
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::rend()
{
    return reverse_iterator(begin_ - 1);
}

template <typename T>
void
Vector<T>::insert(iterator pos, const int n, const value_type& x)
{
    assert(pos.ptr_ >= begin_ && pos.ptr_ <= end_);
    const size_t temp = end_ - pos.ptr_;
    this->reserve(size() + n);
    pos.ptr_ = end_ - temp;
    end_ += n;
    iterator it = end();
    for ( ; it >= pos + n; --it) {
        *(it) = *(it - n);
    }
    while (it >= pos) {
        *it = x;
        --it;
    }
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::insert(iterator pos, const value_type& x)
{
    assert(pos.ptr_ >= begin_ && pos.ptr_ <= end_);
    const size_type temp = end_ - pos.ptr_;
    this->reserve(size() + 1);
    pos.ptr_ = end_ - temp;
    ++end_;
    iterator it = end();
    for ( ; it >= pos + 1; --it) {
        *(it) = *(it - 1);
    }
    *it = x;
    return pos;
}


template <typename T>
template <typename InputIterator>
void
Vector<T>::insert(iterator pos, InputIterator f, InputIterator l)
{
    assert(pos.ptr_ >= begin_ && pos.ptr_ <= end_);
    const difference_type  s = l.ptr_ - f.ptr_;
    const size_type temp = pos.ptr_ - begin_;
    insert(pos, s, value_type());
    pos.ptr_ = begin_ + temp;
    for (InputIterator it = f; it < l; ++it, ++pos) {
        *pos = *it;
    }
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator pos)
{
    assert(pos >= begin() && pos < end());
    iterator it = pos;
    for ( ; it < end(); ++it) {
        *it = *(it + 1);
    }
    pop_back();
    return pos;
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator f, iterator l)
{
    assert(f >= begin() && f <= l);
    assert(l >= f && f <= end() && l <= end());
    const difference_type n = l.ptr_ - f.ptr_;
    for (int i = 0; i < n; ++i, ++f, ++l) {
        *f = *l;    
    }
    for (int i = 0; i < n; ++i) {
        pop_back();
    }
    return f;    
}

/// const_iterator implementation /////////////////////////////////////

template <typename T>
Vector<T>::const_iterator::const_iterator(pointer ptr)
    : ptr_(ptr)
{
}

template <typename T>
Vector<T>::const_iterator::const_iterator()
    : ptr_(NULL)
{
}


template <typename T>
Vector<T>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr_(rhv.ptr_)
{
}

template <typename T>
Vector<T>::const_iterator::~const_iterator()
{
    ptr_ = NULL;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator=(const const_iterator& rhv)
{
    this->ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
const T&
Vector<T>::const_iterator::operator*() const
{
    assert(ptr_ != NULL);
    return *ptr_;
}

template <typename T>
const T*
Vector<T>::const_iterator::operator->() const
{
    assert(ptr_ != NULL);
    return ptr_;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator++()
{
    assert(ptr_ != NULL);
    ++ptr_;
    return *this; 
}

template <typename T>
const typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator++(value_type)
{
    assert(ptr_ != NULL);
    const_iterator temp;
    temp.ptr_ = ++ptr_;
    return temp; 
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator--()
{
    assert(ptr_ != NULL);
    --ptr_;
    return *this; 
}

template <typename T>
const typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator--(value_type)
{
    assert(ptr_ != NULL);
    const_iterator temp;
    temp.ptr_ = --ptr_;
    return temp; 
}

template <typename T>
const typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator+=(const size_type i)
{
    ptr_ += i;
    return const_iterator(ptr_);
}

template <typename T>
const typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator-=(const size_type i)
{
    ptr_ -= i;
    return const_iterator(ptr_);
}

template <typename T>
const typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator+(const size_type i) const
{
    return const_iterator(ptr_ + i);
}

template <typename T>
const typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator-(const size_type i) const
{
    return const_iterator(ptr_ - i);
}

template <typename T>
bool
Vector<T>::const_iterator::operator==(const const_iterator& rhv) const
{
    return this->ptr_ == rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return this->ptr_ != rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator<(const const_iterator& rhv) const
{
    return this->ptr_ < rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator<=(const const_iterator& rhv) const
{
    return this->ptr_ <= rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator>(const const_iterator& rhv) const
{
    return this->ptr_ > rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator>=(const const_iterator& rhv) const
{
    return this->ptr_ >= rhv.ptr_;
}

/// iterator implementation /////////////////////////////////////

template <typename T>
Vector<T>::iterator::iterator(pointer ptr)
    : const_iterator(ptr)
{
}

template <typename T>
Vector<T>::iterator::iterator()
    : const_iterator(NULL)
{
}


template <typename T>
Vector<T>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv.ptr_)
{
}

template <typename T>
Vector<T>::iterator::~iterator()
{
    const_iterator::ptr_ = NULL;
}

template <typename T>
T&
Vector<T>::iterator::operator*()
{
    assert(const_iterator::ptr_ != NULL);
    return *const_iterator::ptr_;
}

template <typename T>
T*
Vector<T>::iterator::operator->()
{
    assert(const_iterator::ptr_ != NULL);
    return const_iterator::ptr_;
}

/// const_reverse_iterator implementation /////////////////////////////////////

template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator()
    : ptr_(NULL)
{
}


template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator(pointer ptr)
    : ptr_(ptr)
{
}

template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator& rhv)
    : ptr_(rhv.ptr_)
{
}

template <typename T>
Vector<T>::const_reverse_iterator::~const_reverse_iterator()
{
    ptr_ = NULL;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
    this->ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
const T&
Vector<T>::const_reverse_iterator::operator*() const
{
    assert(ptr_ != NULL);
    return *ptr_;
}

template <typename T>
const T*
Vector<T>::const_reverse_iterator::operator->() const
{
    assert(ptr_ != NULL);
    return ptr_;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator++()
{
    assert(ptr_ != NULL);
    --ptr_;
    return *this; 
}

template <typename T>
const typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator++(value_type)
{
    assert(ptr_ != NULL);
    const_reverse_iterator temp;
    temp.ptr_ = --ptr_;
    return temp; 
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator--()
{
    assert(ptr_ != NULL);
    ++ptr_;
    return *this; 
}

template <typename T>
const typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator--(value_type)
{
    assert(ptr_ != NULL);
    const_reverse_iterator temp;
    temp.ptr_ = ++ptr_;
    return temp; 
}

template <typename T>
const typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator+=(const size_type i)
{
    ptr_ -= i;
    return const_reverse_iterator(ptr_);
}

template <typename T>
const typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator-=(const size_type i)
{
    ptr_ += i;
    return const_reverse_iterator(ptr_);
}

template <typename T>
const typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator+(const size_type i) const
{
    return const_reverse_iterator(ptr_ - i);
}

template <typename T>
const typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator-(const size_type i) const
{
    return const_reverse_iterator(ptr_ + i);
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator==(const const_reverse_iterator& rhv) const
{
    return this->ptr_ == rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator!=(const const_reverse_iterator& rhv) const
{
    return this->ptr_ != rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator<(const const_reverse_iterator& rhv) const
{
    return this->ptr_ > rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator<=(const const_reverse_iterator& rhv) const
{
    return this->ptr_ >= rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator>(const const_reverse_iterator& rhv) const
{
    return this->ptr_ < rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator>=(const const_reverse_iterator& rhv) const
{
    return this->ptr_ <= rhv.ptr_;
}

/// reverse_iterator implementation ///////////////////////////////

template <typename T>
Vector<T>::reverse_iterator::reverse_iterator()
    : const_reverse_iterator(NULL)
{
}


template <typename T>
Vector<T>::reverse_iterator::reverse_iterator(pointer ptr)
    : const_reverse_iterator(ptr)
{
}

template <typename T>
Vector<T>::reverse_iterator::reverse_iterator(const reverse_iterator& rhv)
    : const_reverse_iterator(rhv.ptr_)
{
}

template <typename T>
Vector<T>::reverse_iterator::~reverse_iterator()
{
    const_reverse_iterator::ptr_ = NULL;
}

template <typename T>
T&
Vector<T>::reverse_iterator::operator*()
{
    assert(const_reverse_iterator::ptr_ != NULL);
    return *const_reverse_iterator::ptr_;
}

template <typename T>
T*
Vector<T>::reverse_iterator::operator->()
{
    assert(const_reverse_iterator::ptr_ != NULL);
    return const_reverse_iterator::ptr_;
}


}

