#include "FrankList.hpp"

#include <cassert>

namespace vhuk {

template <typename T>
std::ostream& operator<<(std::ostream& out, const FrankList<T>& rhv)
{
    out << "{ ";
    for (auto it = rhv.cbegin(); it != rhv.cend(); ++it) {
        out << *it << " ";
    }
    out << "}";
    return out;
}

template <typename T>
FrankList<T>::Node::Node()
    : val(T())
    , next(nullptr)
    , prev(nullptr)
    , asc(nullptr)
    , desc(nullptr)
{}

template <typename T>
FrankList<T>::Node::Node(T val)
    : val(val)
    , next(nullptr)
    , prev(nullptr)
    , asc(nullptr)
    , desc(nullptr)
{}

template <typename T>
FrankList<T>::FrankList()
    : head(nullptr)
    , tail(nullptr)
    , ahead(nullptr)
    , atail(nullptr)
{}

template <typename T>
FrankList<T>::FrankList(size_type size)
    : head(nullptr)
    , tail(nullptr)
    , ahead(nullptr)
    , atail(nullptr)
{
    for (size_type i = 0; i < size; ++i) {
        push_back(value_type());
    }
}

template <typename T>
FrankList<T>::FrankList(size_type size, const_reference init)
    : head(nullptr)
    , tail(nullptr)
    , ahead(nullptr)
    , atail(nullptr)
{
    for (size_type i = 0; i < size; ++i) {
        push_back(init);
    }
}

template <typename T>
FrankList<T>::FrankList(const FrankList<T>& rhv)
    : head(nullptr)
    , tail(nullptr)
    , ahead(nullptr)
    , atail(nullptr)
{
    for (auto it = rhv.cbegin(); it != rhv.cend(); ++it) {
        push_back(*it);
    }
}

template <typename T>
FrankList<T>::FrankList(FrankList<T>&& rhv)
    : head(rhv.head)
    , tail(rhv.tail)
    , ahead(rhv.ahead)
    , atail(rhv.atail)
{
    rhv.head = nullptr;
    rhv.tail = nullptr;
    rhv.ahead = nullptr;
    rhv.atail = nullptr;
}

template <typename T>
FrankList<T>::FrankList(std::initializer_list<T> init)
    : head(nullptr)
    , tail(nullptr)
    , ahead(nullptr)
    , atail(nullptr)
{
    for (auto i : init) {
        push_back(i);
    }
}

template <typename T>
template <typename input_iterator>
FrankList<T>::FrankList(input_iterator f, input_iterator l)
    : head(nullptr)
    , tail(nullptr)
    , ahead(nullptr)
    , atail(nullptr)
{
    for (input_iterator it = f; it != l; ++it) {
        push_back(*it);
    }
}

template <typename T>
FrankList<T>::~FrankList()
{
    clear();
}

template <typename T>
void
FrankList<T>::swap(FrankList<T>& rhv)
{
    std::swap(this->head, rhv.head);
    std::swap(this->tail, rhv.tail);
    std::swap(this->ahead, rhv.ahead);
    std::swap(this->atail, rhv.atail);
}

template <typename T>
typename FrankList<T>::size_type
FrankList<T>::size() const
{
    size_type s = 0;
    for (auto it = cbegin(); it != cend(); ++it) {
        ++s;
    }
    return s;
}

template <typename T>
bool
FrankList<T>::empty() const
{
    return !head;
}

template <typename T>
void
FrankList<T>::resize(size_type s, const_reference init)
{
    size_type m_s = size();
    if (s < m_s) {
        for (size_type i = 0; i < m_s - s; ++i) {
            pop_back();
        }
    }
    else {
        for (size_type i = 0; i < s - m_s; ++i) {
            push_back(init);
        }
    }
}

template <typename T>
void
FrankList<T>::clear() noexcept
{
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
    tail = nullptr;
    ahead = nullptr;
    atail = nullptr;
}

template <typename T>
void
FrankList<T>::push_front(const_reference elem)
{
    Node* tmp = new Node(elem);
    if (!head) {
        head = tmp;
        tail = head;
    }
    else {
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
    }
    put_in_sorted_order(head);
}

template <typename T>
void
FrankList<T>::pop_front()
{
    assert(head != nullptr);
    
    if (!head->next) {
        clear();
        return;
    }
    if (head->asc) {
        head->asc->desc = head->desc;
    }
    if (head->desc) {
        head->desc->asc = head->asc;
    }
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
}

template <typename T>
void
FrankList<T>::push_back(const_reference elem)
{
    Node* tmp = new Node(elem);
    if (!head) {
        head = tmp;
        tail = head;
    }
    else {
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
    }
    put_in_sorted_order(tail);
}

template <typename T>
void
FrankList<T>::pop_back()
{
    assert(head != nullptr);

    if (!head->next) {
        clear();
        return;
    }
    if (tail->asc) {
        tail->asc->desc = tail->desc;
    }
    if (tail->desc) {
        tail->desc->asc = tail->asc;
    }

    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::front() const
{
    assert(head != nullptr);
    return head->val;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::front()
{
    assert(head != nullptr);
    return head->val;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::back() const
{
    assert(head != nullptr);
    return tail->val;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::back()
{
    assert(head != nullptr);
    return tail->val;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::min() const
{
    assert(head != nullptr);
    return ahead->val;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::min()
{
    assert(head != nullptr);
    return ahead->val;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::max() const
{
    assert(head != nullptr);
    return atail->val;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::max()
{
    assert(head != nullptr);
    return atail->val;
}

template <typename T>
const FrankList<T>&
FrankList<T>::operator=(const FrankList<T>& rhv)
{
    if (this == &rhv) {
        return *this;
    }
    clear();
    for (auto it = rhv.cbegin(); it != rhv.cend(); ++it) {
        push_back(*it);
    }
    return *this;
}

template <typename T>
const FrankList<T>&
FrankList<T>::operator=(FrankList<T>&& rhv)
{
    clear();
    head = rhv.head;
    tail = rhv.tail;
    ahead = rhv.ahead;
    atail = rhv.atail;

    rhv.head = nullptr;
    rhv.tail = nullptr;
    rhv.ahead = nullptr;
    rhv.atail = nullptr;

    return *this;
}

template <typename T>
const FrankList<T>&
FrankList<T>::operator=(std::initializer_list<T> init)
{
    clear();

    for (auto i : init) {
        push_back(i);
    }
    return *this;
}

template <typename T>
bool
FrankList<T>::operator==(const FrankList<T>& rhv) const
{
    if (this->size() != rhv.size()) {
        return false;
    }
    Node* it1 = ahead;
    Node* it2 = rhv.ahead;
    for (; it1; it1 = it1->next, it2 = it2->next) {
        if (it1->val != it2->val) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool
FrankList<T>::operator!=(const FrankList<T>& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
FrankList<T>::operator<(const FrankList<T>& rhv) const
{
    size_type s1 = this->size();
    size_type s2 = rhv.size();
    if (s1 < s2) {
        return true;
    }
    if (s1 == s2) {
        Node* it1 = ahead;
        Node* it2 = rhv.ahead;
        for (; it1; it1 = it1->next, it2 = it2->next) {
            if (it1->val < it2->val) {
                return true;
            }
            if (it1->val > it2->val) {
                return false;
            }
        }
    }
    return false;
}

template <typename T>
bool
FrankList<T>::operator<=(const FrankList<T>& rhv) const
{
    return (*this < rhv || *this == rhv);
}

template <typename T>
bool
FrankList<T>::operator>(const FrankList<T>& rhv) const
{
    return !(*this <= rhv);
}

template <typename T>
bool
FrankList<T>::operator>=(const FrankList<T>& rhv) const
{
    return !(*this < rhv);
}

template <typename T>
typename FrankList<T>::const_iterator
FrankList<T>::cbegin() const
{
    return const_iterator(head);
}

template <typename T>
typename FrankList<T>::const_iterator
FrankList<T>::cend() const
{
    return const_iterator(tail->next);
}

template <typename T>
typename FrankList<T>::const_reverse_iterator
FrankList<T>::crbegin() const
{
    return const_reverse_iterator(tail);
}

template <typename T>
typename FrankList<T>::const_reverse_iterator
FrankList<T>::crend() const
{
    return const_reverse_iterator(head->prev);
}

template <typename T>
typename FrankList<T>::const_asc_iterator
FrankList<T>::cabegin() const
{
    return const_asc_iterator(ahead);
}

template <typename T>
typename FrankList<T>::const_asc_iterator
FrankList<T>::caend() const
{
    return const_asc_iterator(atail->asc);
}

template <typename T>
typename FrankList<T>::const_desc_iterator
FrankList<T>::cdbegin() const
{
    return const_desc_iterator(atail);
}

template <typename T>
typename FrankList<T>::const_desc_iterator
FrankList<T>::cdend() const
{
    return const_desc_iterator(ahead->desc);
}

template <typename T>
typename FrankList<T>::const_multi_iterator
FrankList<T>::cmbegin() const
{
    return const_multi_iterator(head);
}

template <typename T>
typename FrankList<T>::const_multi_iterator
FrankList<T>::cmend() const
{
    return const_iterator(tail->next);
}

template <typename T>
typename FrankList<T>::const_multi_iterator
FrankList<T>::cmabegin() const
{
    return const_multi_iterator(ahead);
}

template <typename T>
typename FrankList<T>::const_multi_iterator
FrankList<T>::cmaend() const
{
    return const_multi_iterator(atail->asc);
}

template <typename T>
typename FrankList<T>::const_multi_reverse_iterator
FrankList<T>::cmrbegin() const
{
    return const_multi_reverse_iterator(tail);
}

template <typename T>
typename FrankList<T>::const_multi_reverse_iterator
FrankList<T>::cmrend() const
{
    return const_iterator(head->prev);
}

template <typename T>
typename FrankList<T>::const_multi_reverse_iterator
FrankList<T>::cmrdbegin() const
{
    return const_multi_reverse_iterator(atail);
}

template <typename T>
typename FrankList<T>::const_multi_reverse_iterator
FrankList<T>::cmrdend() const
{
    return const_multi_reverse_iterator(ahead->desc);
}

template <typename T>
typename FrankList<T>::iterator
FrankList<T>::begin() 
{
    return iterator(head);
}

template <typename T>
typename FrankList<T>::iterator
FrankList<T>::end() 
{
    return iterator(tail->next);
}

template <typename T>
typename FrankList<T>::reverse_iterator
FrankList<T>::rbegin() 
{
    return reverse_iterator(tail);
}

template <typename T>
typename FrankList<T>::reverse_iterator
FrankList<T>::rend() 
{
    return reverse_iterator(head->prev);
}

template <typename T>
typename FrankList<T>::asc_iterator
FrankList<T>::abegin() 
{
    return asc_iterator(ahead);
}

template <typename T>
typename FrankList<T>::asc_iterator
FrankList<T>::aend() 
{
    return asc_iterator(atail->asc);
}

template <typename T>
typename FrankList<T>::desc_iterator
FrankList<T>::dbegin() 
{
    return desc_iterator(atail);
}

template <typename T>
typename FrankList<T>::desc_iterator
FrankList<T>::dend() 
{
    return desc_iterator(ahead->desc);
}

template <typename T>
typename FrankList<T>::multi_iterator
FrankList<T>::mbegin() 
{
    return multi_iterator(head);
}

template <typename T>
typename FrankList<T>::multi_iterator
FrankList<T>::mend() 
{
    return iterator(tail->next);
}

template <typename T>
typename FrankList<T>::multi_iterator
FrankList<T>::mabegin() 
{
    return multi_iterator(ahead);
}

template <typename T>
typename FrankList<T>::multi_iterator
FrankList<T>::maend() 
{
    return multi_iterator(atail->as);
}

template <typename T>
typename FrankList<T>::multi_reverse_iterator
FrankList<T>::mrbegin() 
{
    return multi_reverse_iterator(tail);
}

template <typename T>
typename FrankList<T>::multi_reverse_iterator
FrankList<T>::mrend() 
{
    return iterator(head->prev);
}

template <typename T>
typename FrankList<T>::multi_reverse_iterator
FrankList<T>::mrdbegin() 
{
    return multi_reverse_iterator(atail);
}

template <typename T>
typename FrankList<T>::multi_reverse_iterator
FrankList<T>::mrdend() 
{
    return multi_reverse_iterator(ahead->des);
}
/*
template <typename T>
template <typename iter>
iter
FrankList<T>::insert(iter pos, const_reference val)
{
    if (std::is_same<T, const_iterator>::value ||
        std::is_same<T, const_asc_iterator>::value ||
        std::is_same<T, const_multi_iterator>::value) {
        return insert_def(pos, val);
    }
    if (std::is_same<T, const_reverse_iterator>::value ||
        std::is_same<T, const_desc_iterator>::value ||
        std::is_same<T, const_multi_reverse_iterator>::value) {
        return insert_rev(pos, val);
    }
    throw std::invalid_argument("uncorrect iterator");
}
*/
template <typename T>
template <typename iter>
iter
FrankList<T>::insert(iter pos, size_type s, const_reference val)
{
    static_assert(std::is_base_of<base_iterator, iter>::value == true, "uncorrect iterator");
    for (size_type i = 0; i < s; ++i) {
        pos = insert(pos, val);
    }
    return pos;
}

template <typename T>
template <typename iter>
iter
FrankList<T>::insert(iter pos, std::initializer_list<T> init)
{
    static_assert(std::is_base_of<base_iterator, iter>::value == true, "uncorrect iterator");
    for (auto i : init) {
        pos = insert(pos, i);
    }
    return pos;
}

template <typename T>
template <typename iter, typename input_iterator>
iter
FrankList<T>::insert(iter pos, input_iterator f, input_iterator l)
{
    static_assert(std::is_base_of<base_iterator, iter>::value == true, "uncorrect iterator");
    for (auto i = f; i != l; ++i) {
        pos = insert(pos, *i);
    }
    return pos;
}

template <typename T>
template <typename iter>
iter
FrankList<T>::erase(iter pos)
{
    static_assert(std::is_base_of<base_iterator, iter>::value == true, "uncorrect iterator");
    Node* ptr = pos.ptr;
    iter tmp(pos);
    ++tmp;
    if (pos.ptr == head) {
        pop_front();
        return tmp;
    }
    if (pos.ptr == tail) {
        pop_back();
        return tmp;
    }

    if (ptr->prev) {
        ptr->prev->next = ptr->next;
    }
    if (ptr->next) {
        ptr->next->prev = ptr->prev;
    }
    if (ptr->desc) {
        ptr->desc->asc = ptr->asc;
    }
    if (ptr->asc) {
        ptr->asc->desc = ptr->desc;
    }
    delete pos.ptr;
    return tmp;
}

template <typename T>
template <typename iter>
iter
FrankList<T>::erase(iter f, iter l)
{
    iter tmp(f);
    while (tmp != l) {
        tmp = erase(tmp);
    }
    return tmp;
}

template <typename T>
typename FrankList<T>::size_type
FrankList<T>::remove(const_reference val)
{
    size_type cnt = 0;
    iterator it = begin();
    while (it != end()) {
        if (*it == val) {
            it = erase(it);
            ++cnt;    
        }
        else {
            ++it;
        }
    }
    return cnt;
}

template <typename T>
template <typename unary_predicate>
typename FrankList<T>::size_type
FrankList<T>::remove_if(unary_predicate func)
{
    size_type cnt = 0;
    iterator it = begin();
    while (it != end()) {
        if (func(*it)) {
            it = erase(it);
            ++cnt;
        }
        else {
            ++it;
        }
    }
    return cnt;
}

template <typename T>
void
FrankList<T>::reverse()
{
    std::swap(head, tail);
    Node* it = head;
    while (it) {
        std::swap(it->next, it->prev);
        it = it->next;
    }
}

template <typename T>
void
FrankList<T>::sort(bool reversed)
{
    if (!ahead) {
        return;
    }
    if (!reversed) {
        head = ahead;
        tail = atail;
        Node* it = ahead;
        if (it->prev) {
            it->prev->next = nullptr;
        }
        it->prev = nullptr;
        while (it) {
            it->next = it->asc;
            if (it->next) {
                it->next->prev = it;
            }
            it = it->next;
        }
    }
    else {
        head = atail;
        tail = ahead;
        Node* it = atail;
        if (it->prev) {
            it->prev->next = nullptr;
        }
        it->next = nullptr;
        while (it) {
            it->next = it->desc;
            if (it->next) {
                it->next->prev = it;
            }
            it = it->next;
        }
    }
}

template <typename T>
typename FrankList<T>::iterator
FrankList<T>::find(const_reference elem)
{
    iterator it = begin();
    while (it != end() && *it != elem) {
        ++it;
    }
    organize_left(it.ptr);
    return iterator(it);
}

template <typename T>
typename FrankList<T>::iterator
FrankList<T>::rfind(const_reference elem)
{
    reverse_iterator it = rbegin();
    while (it != rend() && *it != elem) {
        ++it;
    }
    organize_right(it.ptr);
    return iterator(it);
}

template <typename T>
template <typename unary_predicate>
void
FrankList<T>::traverse(unary_predicate func, bool sorted, bool reversed)
{
    if (!head) {
        return;
    }
    if (!sorted && !reversed) {
        for (auto it = begin(); it != end(); ++it) {
            func(*it);
        }
    }
    else if (!sorted) {
        for (auto it = rbegin(); it != rend(); ++it) {
            func(*it);
        }
    }
    else if (!reversed) {
        for (auto it = abegin(); it != aend(); ++it) {
            func(*it);
        }
    }
    else {
        for (auto it = dbegin(); it != dend(); ++it) {
            func(*it);
        }
    }
}

template <typename T>
void
FrankList<T>::print(bool sorted, bool reversed)
{
    if (!head) {
        std::cout << "{  }";
        return;
    }
    std::cout << "{ ";
    if (!sorted && !reversed) {
        for (auto it = begin(); it != end(); ++it) {
            std::cout << *it << " ";
        }
    }
    else if (!sorted) {
        for (auto it = rbegin(); it != rend(); ++it) {
            std::cout << *it << " ";
        }
    }
    else if (!reversed) {
        for (auto it = abegin(); it != aend(); ++it) {
            std::cout << *it << " ";
        }
    }
    else {
        for (auto it = dbegin(); it != dend(); ++it) {
            std::cout << *it << " ";
        }
    }
    std::cout << "}";
}

template <typename T>
void
FrankList<T>::put_in_sorted_order(Node* ptr)
{
    assert(ptr != nullptr);
    if (!ahead) {
        ahead = ptr;
        atail = ptr;
        return;
    }
    Node* it = ahead;
    while (it->val <= ptr->val && it->asc) {
        it = it->asc;
    }

    if (it->val < ptr->val) {
        ptr->asc = it->asc;
        it->asc = ptr;
        ptr->desc = it;
        if (!ptr->asc) {
            atail = ptr;
        }
    }
    else {
        ptr->desc = it->desc;
        if (it->desc) {
            it->desc->asc = ptr;
        }
        else {
            ahead = ptr;
        }
        ptr->asc = it;
        it->desc = ptr;
    }


}

template <typename T>
void
FrankList<T>::organize_left(Node* ptr)
{
    assert(ptr != nullptr);
    if (ptr == head) {
        return;
    }
    Node* prev = ptr->prev;
    Node* next = ptr->next;
    if (prev) {
        if (prev->prev) {
            prev->prev->next = ptr;
        }
            ptr->prev = prev->prev;
        prev->prev = ptr;
        prev->next = next;
        ptr->next = prev;
    }
    if (next) {
        next->prev = prev;
    }
    if (prev == head) {
        head = ptr;
    }
    if (ptr == tail) {
        tail = prev;
    }
}

template <typename T>
void
FrankList<T>::organize_right(Node* ptr)
{
    assert(ptr != nullptr);
    if (ptr == tail) {
        return;
    }
    Node* prev = ptr->prev;
    Node* next = ptr->next;
    if (next) {
        if (next->next) {
            next->next->prev = ptr;
        }
            ptr->next = next->next;
        next->next = ptr;
        next->prev = prev;
        ptr->prev = next;
    }
    if (prev) {
        prev->next = next;
    }
    if (next == tail) {
        tail = ptr;
    }
    if (ptr == head) {
        head = next;
    }
}

template <typename T>
template <typename iter>
iter
FrankList<T>::insert_def(iter pos, const_reference val)
{
    assert(pos.ptr != nullptr);
    if (pos.ptr == head) {
        push_front(val);
    }
    else {
        Node* tmp = new Node(val);
        pos.ptr->prev->next = tmp;
        tmp->prev = pos.ptr->prev;
        pos.ptr->prev = tmp;
        tmp->next = pos.ptr;
        
        put_in_sorted_order(tmp);
    }
    return pos;
}

template <typename T>
template <typename iter>
iter
FrankList<T>::insert_rev(iter pos, const_reference val)
{
    assert(pos.ptr != nullptr);
    insert_def(pos, val);
    ++pos;
    return pos;
}

// ITERATORS ###############################################

template <typename T>
FrankList<T>::base_iterator::base_iterator(Node* ptr)
    : ptr(ptr)
{}

template <typename T>
FrankList<T>::base_iterator::~base_iterator()
{
    ptr = nullptr;
}

template <typename T>
bool
FrankList<T>::base_iterator::operator==(const base_iterator& rhv) const
{
    return (ptr == rhv.ptr);
}

template <typename T>
bool
FrankList<T>::base_iterator::operator!=(const base_iterator& rhv) const
{
    return (ptr != rhv.ptr);
}

template <typename T>
FrankList<T>::const_iterator::const_iterator(const base_iterator& rhv)
    : base_iterator(rhv.ptr)
{}


template <typename T>
FrankList<T>::const_iterator::const_iterator(base_iterator&& rhv)
    : base_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
FrankList<T>::const_iterator::const_iterator(Node* ptr)
    : base_iterator(ptr)
{}

template <typename T>
const typename FrankList<T>::const_iterator&
FrankList<T>::const_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_iterator&
FrankList<T>::const_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::const_iterator::operator*() const
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::const_pointer
FrankList<T>::const_iterator::operator->() const
{
    return this->ptr;
}

template <typename T>
const typename FrankList<T>::const_iterator&
FrankList<T>::const_iterator::operator++()
{
    this->ptr = this->ptr->next;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_iterator
FrankList<T>::const_iterator::operator++(value_type)
{
    const_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
const typename FrankList<T>::const_iterator&
FrankList<T>::const_iterator::operator--()
{
    this->ptr = this->ptr->prev;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_iterator
FrankList<T>::const_iterator::operator--(value_type)
{
    const_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T>
FrankList<T>::iterator::iterator(Node* ptr)
    : const_iterator(ptr)
{}

template <typename T>
FrankList<T>::iterator::iterator(const base_iterator& rhv)
    : const_iterator(rhv.ptr)
{}

template <typename T>
FrankList<T>::iterator::iterator(base_iterator&& rhv)
    : const_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::iterator&
FrankList<T>::iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::iterator&
FrankList<T>::iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::iterator::operator*()
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::pointer
FrankList<T>::iterator::operator->()
{
    return this->ptr;
}

template <typename T>
FrankList<T>::const_reverse_iterator::const_reverse_iterator(const base_iterator& rhv)
    : base_iterator(rhv.ptr)
{}


template <typename T>
FrankList<T>::const_reverse_iterator::const_reverse_iterator(base_iterator&& rhv)
    : base_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
FrankList<T>::const_reverse_iterator::const_reverse_iterator(Node* ptr)
    : base_iterator(ptr)
{}

template <typename T>
const typename FrankList<T>::const_reverse_iterator&
FrankList<T>::const_reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_reverse_iterator&
FrankList<T>::const_reverse_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::const_reverse_iterator::operator*() const
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::const_pointer
FrankList<T>::const_reverse_iterator::operator->() const
{
    return this->ptr;
}

template <typename T>
const typename FrankList<T>::const_reverse_iterator&
FrankList<T>::const_reverse_iterator::operator++()
{
    this->ptr = this->ptr->prev;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_reverse_iterator
FrankList<T>::const_reverse_iterator::operator++(value_type)
{
    const_reverse_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
const typename FrankList<T>::const_reverse_iterator&
FrankList<T>::const_reverse_iterator::operator--()
{
    this->ptr = this->ptr->next;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_reverse_iterator
FrankList<T>::const_reverse_iterator::operator--(value_type)
{
    const_reverse_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T>
FrankList<T>::reverse_iterator::reverse_iterator(Node* ptr)
    : const_reverse_iterator(ptr)
{}

template <typename T>
FrankList<T>::reverse_iterator::reverse_iterator(const base_iterator& rhv)
    : const_reverse_iterator(rhv.ptr)
{}

template <typename T>
FrankList<T>::reverse_iterator::reverse_iterator(base_iterator&& rhv)
    : const_reverse_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::reverse_iterator&
FrankList<T>::reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::reverse_iterator&
FrankList<T>::reverse_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::reverse_iterator::operator*()
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::pointer
FrankList<T>::reverse_iterator::operator->()
{
    return this->ptr;
}

template <typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(const base_iterator& rhv)
    : base_iterator(rhv.ptr)
{}


template <typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(base_iterator&& rhv)
    : base_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(Node* ptr)
    : base_iterator(ptr)
{}

template <typename T>
const typename FrankList<T>::const_asc_iterator&
FrankList<T>::const_asc_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_asc_iterator&
FrankList<T>::const_asc_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::const_asc_iterator::operator*() const
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::const_pointer
FrankList<T>::const_asc_iterator::operator->() const
{
    return this->ptr;
}

template <typename T>
const typename FrankList<T>::const_asc_iterator&
FrankList<T>::const_asc_iterator::operator++()
{
    this->ptr = this->ptr->asc;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_asc_iterator
FrankList<T>::const_asc_iterator::operator++(value_type)
{
    const_asc_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
const typename FrankList<T>::const_asc_iterator&
FrankList<T>::const_asc_iterator::operator--()
{
    this->ptr = this->ptr->desc;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_asc_iterator
FrankList<T>::const_asc_iterator::operator--(value_type)
{
    const_asc_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T>
FrankList<T>::asc_iterator::asc_iterator(Node* ptr)
    : const_asc_iterator(ptr)
{}

template <typename T>
FrankList<T>::asc_iterator::asc_iterator(const base_iterator& rhv)
    : const_asc_iterator(rhv.ptr)
{}

template <typename T>
FrankList<T>::asc_iterator::asc_iterator(base_iterator&& rhv)
    : const_asc_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::asc_iterator&
FrankList<T>::asc_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::asc_iterator&
FrankList<T>::asc_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::asc_iterator::operator*()
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::pointer
FrankList<T>::asc_iterator::operator->()
{
    return this->ptr;
}

template <typename T>
FrankList<T>::const_desc_iterator::const_desc_iterator(const base_iterator& rhv)
    : base_iterator(rhv.ptr)
{}


template <typename T>
FrankList<T>::const_desc_iterator::const_desc_iterator(base_iterator&& rhv)
    : base_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
FrankList<T>::const_desc_iterator::const_desc_iterator(Node* ptr)
    : base_iterator(ptr)
{}

template <typename T>
const typename FrankList<T>::const_desc_iterator&
FrankList<T>::const_desc_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_desc_iterator&
FrankList<T>::const_desc_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::const_desc_iterator::operator*() const
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::const_pointer
FrankList<T>::const_desc_iterator::operator->() const
{
    return this->ptr;
}

template <typename T>
const typename FrankList<T>::const_desc_iterator&
FrankList<T>::const_desc_iterator::operator++()
{
    this->ptr = this->ptr->desc;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_desc_iterator
FrankList<T>::const_desc_iterator::operator++(value_type)
{
    const_desc_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
const typename FrankList<T>::const_desc_iterator&
FrankList<T>::const_desc_iterator::operator--()
{
    this->ptr = this->ptr->asc;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_desc_iterator
FrankList<T>::const_desc_iterator::operator--(value_type)
{
    const_desc_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T>
FrankList<T>::desc_iterator::desc_iterator(Node* ptr)
    : const_desc_iterator(ptr)
{}

template <typename T>
FrankList<T>::desc_iterator::desc_iterator(const base_iterator& rhv)
    : const_desc_iterator(rhv.ptr)
{}

template <typename T>
FrankList<T>::desc_iterator::desc_iterator(base_iterator&& rhv)
    : const_desc_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::desc_iterator&
FrankList<T>::desc_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::desc_iterator&
FrankList<T>::desc_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::desc_iterator::operator*()
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::pointer
FrankList<T>::desc_iterator::operator->()
{
    return this->ptr;
}

template <typename T>
FrankList<T>::const_multi_iterator::const_multi_iterator(const base_iterator& rhv)
    : base_iterator(rhv.ptr)
{}


template <typename T>
FrankList<T>::const_multi_iterator::const_multi_iterator(base_iterator&& rhv)
    : base_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
FrankList<T>::const_multi_iterator::const_multi_iterator(Node* ptr)
    : base_iterator(ptr)
{}

template <typename T>
const typename FrankList<T>::const_multi_iterator&
FrankList<T>::const_multi_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_iterator&
FrankList<T>::const_multi_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::const_multi_iterator::operator*() const
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::const_pointer
FrankList<T>::const_multi_iterator::operator->() const
{
    return this->ptr;
}

template <typename T>
const typename FrankList<T>::const_multi_iterator&
FrankList<T>::const_multi_iterator::operator++()
{
    if (mode) {
        this->ptr = this->ptr->next;
    }
    else {
        this->ptr = this->ptr->asc;
    }
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_iterator
FrankList<T>::const_multi_iterator::operator++(value_type)
{
    const_multi_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
const typename FrankList<T>::const_multi_iterator&
FrankList<T>::const_multi_iterator::operator--()
{
    if (mode) {
        this->ptr = this->ptr->desc;
    }
    else {
        this->ptr = this->ptr->prev;
    }
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_iterator
FrankList<T>::const_multi_iterator::operator--(value_type)
{
    const_multi_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T>
void
FrankList<T>::const_multi_iterator::chmod()
{
    mode = !mode;
}

template <typename T>
FrankList<T>::multi_iterator::multi_iterator(Node* ptr)
    : const_multi_iterator(ptr)
{}

template <typename T>
FrankList<T>::multi_iterator::multi_iterator(const base_iterator& rhv)
    : const_multi_iterator(rhv.ptr)
{}

template <typename T>
FrankList<T>::multi_iterator::multi_iterator(base_iterator&& rhv)
    : const_multi_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::multi_iterator&
FrankList<T>::multi_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::multi_iterator&
FrankList<T>::multi_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::multi_iterator::operator*()
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::pointer
FrankList<T>::multi_iterator::operator->()
{
    return this->ptr;
}

template <typename T>
FrankList<T>::const_multi_reverse_iterator::const_multi_reverse_iterator(const base_iterator& rhv)
    : base_iterator(rhv.ptr)
{}


template <typename T>
FrankList<T>::const_multi_reverse_iterator::const_multi_reverse_iterator(base_iterator&& rhv)
    : base_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
FrankList<T>::const_multi_reverse_iterator::const_multi_reverse_iterator(Node* ptr)
    : base_iterator(ptr)
{}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator&
FrankList<T>::const_multi_reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator&
FrankList<T>::const_multi_reverse_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::const_reference
FrankList<T>::const_multi_reverse_iterator::operator*() const
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::const_pointer
FrankList<T>::const_multi_reverse_iterator::operator->() const
{
    return this->ptr;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator&
FrankList<T>::const_multi_reverse_iterator::operator++()
{
    if (mode) {
        this->ptr = this->ptr->prev;
    }
    else {
        this->ptr = this->ptr->desc;
    }
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator
FrankList<T>::const_multi_reverse_iterator::operator++(value_type)
{
    const_multi_reverse_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator&
FrankList<T>::const_multi_reverse_iterator::operator--()
{
    if (mode) {
        this->ptr = this->ptr->next;
    }
    else {
        this->ptr = this->ptr->asc;
    }
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator
FrankList<T>::const_multi_reverse_iterator::operator--(value_type)
{
    const_multi_reverse_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T>
void
FrankList<T>::const_multi_reverse_iterator::chmod()
{
    mode = !mode;
}

template <typename T>
FrankList<T>::multi_reverse_iterator::multi_reverse_iterator(Node* ptr)
    : const_multi_reverse_iterator(ptr)
{}

template <typename T>
FrankList<T>::multi_reverse_iterator::multi_reverse_iterator(const base_iterator& rhv)
    : const_multi_reverse_iterator(rhv.ptr)
{}

template <typename T>
FrankList<T>::multi_reverse_iterator::multi_reverse_iterator(base_iterator&& rhv)
    : const_multi_reverse_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::multi_reverse_iterator&
FrankList<T>::multi_reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::multi_reverse_iterator&
FrankList<T>::multi_reverse_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::multi_reverse_iterator::operator*()
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::pointer
FrankList<T>::multi_reverse_iterator::operator->()
{
    return this->ptr;
}

}

