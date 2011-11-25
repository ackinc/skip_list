//==============================================================================
// skip_list.h
// Copyright (c) 2011 Pete Goodliffe. All rights reserved
//==============================================================================

#pragma once

#include <memory>     // for std::allocator
#include <functional> // for std::less

#include <cassert>
void not_implemented_yet();
inline
void not_implemented_yet() { assert("Not implemented yet" && false); }

/// STL-style skip list container
///
/// C++11: noexcept decls
template <typename T,
          typename Compare   = std::less<T>,
          typename Allocator = std::allocator<T> >
class skip_list
{
public:

    //======================================================================
    // types

    typedef T                 value_type;
    typedef Allocator         allocator_type;
    typedef size_t            size_type;
    typedef ptrdiff_t         difference_type;
    typedef Compare           compare;

    // pre C++11
    typedef value_type       &reference;
    typedef const value_type &const_reference;
    typedef T                *pointer;
    typedef const T          *const_pointer;

    // C++11
    //typedef Allocator::reference                            reference;
    //typedef Allocator::const_reference                      const_reference;
    //typedef std::allocator_traits<Allocator>::pointer       pointer;
    //typedef std::allocator_traits<Allocator>::const_pointer const_pointer;

    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    //======================================================================
    // lifetime management

    explicit skip_list(const Allocator &alloc = Allocator());

    template <class InputIterator>
    skip_list(InputIterator first, InputIterator last, const Allocator &alloc = Allocator());

    skip_list(const skip_list &other);
    skip_list(const skip_list &other, const Allocator &alloc);

    // C++11
    //skip_list(const skip_list &&other);
    //skip_list(const skip_list &&other, const Allocator &alloc);
    //skip_list(std::initializer_list<T> init, const Allocator &alloc = Allocator());

    ~skip_list();

    allocator_type get_allocator() const;

    //======================================================================
    // assignment

    skip_list &operator=(const skip_list &other);
    //C++11 skip_list& operator=(skip_list&& other);

    void assign(size_type count, const value_type &value);

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last);

    //======================================================================
    // element access

    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;

    //======================================================================
    // iterators

    iterator       begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator       end();
    const_iterator end() const;
    const_iterator cend() const;

    reverse_iterator       rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;

    reverse_iterator       rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    //======================================================================
    // capacity

    bool      empty() const;
    size_type size() const;
    size_type max_size() const;

    //======================================================================
    // modifiers

    void clear();

    iterator insert(const_iterator pos, const value_type &value);

    //C++11iterator insert const_iterator pos, value_type &&value);

    iterator insert(const_iterator pos, size_type count, const value_type &value);

    template <class InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last);

    //C++11iterator insert(const_iterator pos, std::initializer_list<value_type> ilist);

    // C++11 emplace
    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);

    void push_back(const value_type &value);
    //C++11void push_back( value_type &&value );

    //C++11 emplace_back

    void swap(skip_list &other);

    friend void swap(skip_list &lhs, skip_list &rhs) { lhs.swap(rhs); }

    //======================================================================
    // other operations

    // std::list has:
    //   * merge
    //   * splice
    //   * remove
    //   * remove_if
    //   * reverse
    //   * unique
    //   * sort

private:
    struct node
    {
        node *next;
        value_type value;
    };

    static const unsigned max_levels = 33;

    const allocator_type alloc;
    unsigned             levels;
    node                *nodes[max_levels];

    unsigned random_level();
};

template <class T, class Compare, class Allocator>
bool operator==(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs);

template <class T, class Compare, class Allocator>
bool operator!=(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs);

template <class T, class Compare, class Allocator>
bool operator<(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs);

template <class T, class Compare, class Allocator>
bool operator<=(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs);

template <class T, class Compare, class Allocator>
bool operator>(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs);

template <class T, class Compare, class Allocator>
bool operator>=(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs);

namespace std
{
    template <class T, class Compare, class Allocator>
    void swap(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs);
}

//==============================================================================
// iterators

template <class T, class Compare, class Allocator>
class skip_list<T,Compare,Allocator>::iterator {};

template <class T, class Compare, class Allocator>
class skip_list<T,Compare,Allocator>::const_iterator {};

template <class T, class Compare, class Allocator>
class skip_list<T,Compare,Allocator>::reverse_iterator {};

template <class T, class Compare, class Allocator>
class skip_list<T,Compare,Allocator>::const_reverse_iterator {};

//==============================================================================
// lifetime management

template <class T, class Compare, class Allocator>
inline
skip_list<T,Compare,Allocator>::skip_list(const Allocator &alloc)
:   alloc(alloc),
    levels()
{
}

template <class T, class Compare, class Allocator>
inline
skip_list<T,Compare,Allocator>::~skip_list()
{
}

template <class T, class Compare, class Allocator>
template <class InputIterator>
inline
skip_list<T,Compare,Allocator>::skip_list(InputIterator first, InputIterator last, const Allocator &alloc)
:   alloc(alloc),
    levels(0)
{
    assert(false);
}

template <class T, class Compare, class Allocator>
inline
skip_list<T,Compare,Allocator>::skip_list(const skip_list &other)
:   alloc(other.alloc),
    levels(0)
{
    assert(false);
}

template <class T, class Compare, class Allocator>
inline
skip_list<T,Compare,Allocator>::skip_list(const skip_list &other, const Allocator &alloc)
:   alloc(alloc),
    levels(0)
{
    assert(false);
}

// C++11
//skip_list(const skip_list &&other);
//skip_list(const skip_list &&other, const Allocator &alloc);
//skip_list(std::initializer_list<T> init, const Allocator &alloc = Allocator());

template <class T, class Compare, class Allocator>
inline
Allocator skip_list<T,Compare,Allocator>::get_allocator() const
{
    return alloc;
}

//==============================================================================
// assignment

template <class T, class Compare, class Allocator>
inline
skip_list<T,Compare,Allocator> &skip_list<T,Compare,Allocator>::operator=(const skip_list<T,Compare,Allocator> &other)
{
    not_implemented_yet();
}

//C++11 skip_list& operator=(skip_list&& other);

template <class T, class Compare, class Allocator>
inline
void skip_list<T,Compare,Allocator>::assign(size_type count, const value_type &value)
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
template <typename InputIterator>
inline
void skip_list<T,Compare,Allocator>::assign(InputIterator first, InputIterator last)
{
    not_implemented_yet();
}

//==============================================================================
// element access

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::reference
skip_list<T,Compare,Allocator>::front()
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_reference
skip_list<T,Compare,Allocator>::front() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::reference
skip_list<T,Compare,Allocator>::back()
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_reference
skip_list<T,Compare,Allocator>::back() const
{
    not_implemented_yet();
}

//==============================================================================
// iterators

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::iterator
skip_list<T,Compare,Allocator>::begin()
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_iterator
skip_list<T,Compare,Allocator>::begin() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_iterator
skip_list<T,Compare,Allocator>::cbegin() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::iterator
skip_list<T,Compare,Allocator>::end()
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_iterator
skip_list<T,Compare,Allocator>::end() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_iterator
skip_list<T,Compare,Allocator>::cend() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::reverse_iterator
skip_list<T,Compare,Allocator>::rbegin()
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_reverse_iterator
skip_list<T,Compare,Allocator>::rbegin() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_reverse_iterator
skip_list<T,Compare,Allocator>::crbegin() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::reverse_iterator
skip_list<T,Compare,Allocator>::rend()
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_reverse_iterator
skip_list<T,Compare,Allocator>::rend() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::const_reverse_iterator
skip_list<T,Compare,Allocator>::crend() const
{
    not_implemented_yet();
}

//==============================================================================
// capacity

template <class T, class Compare, class Allocator>
inline
bool skip_list<T,Compare,Allocator>::empty() const
{
    return levels == 0;
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::size_type
skip_list<T,Compare,Allocator>::size() const
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::size_type
skip_list<T,Compare,Allocator>::max_size() const
{
    not_implemented_yet();
}

//==============================================================================
// modifiers

template <class T, class Compare, class Allocator>
inline
void skip_list<T,Compare,Allocator>::clear()
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::iterator
skip_list<T,Compare,Allocator>::insert(const_iterator pos, const value_type &value)
{
    not_implemented_yet();
}

//C++11iterator insert const_iterator pos, value_type &&value);

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::iterator
skip_list<T,Compare,Allocator>::insert(const_iterator pos, size_type count, const value_type &value)
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
template <class InputIterator>
inline
typename skip_list<T,Compare,Allocator>::iterator
skip_list<T,Compare,Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
{
    not_implemented_yet();
}

//C++11iterator insert(const_iterator pos, std::initializer_list<value_type> ilist);
// C++11 emplace

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::iterator
skip_list<T,Compare,Allocator>::erase(const_iterator position)
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
typename skip_list<T,Compare,Allocator>::iterator
skip_list<T,Compare,Allocator>::erase(const_iterator first, const_iterator last)
{
    not_implemented_yet();
}

template <class T, class Compare, class Allocator>
inline
void skip_list<T,Compare,Allocator>::push_back(const value_type &value)
{
    not_implemented_yet();
}

//C++11void push_back( value_type &&value );
//C++11 emplace_back

template <class T, class Compare, class Allocator>
inline
void skip_list<T,Compare,Allocator>::swap(skip_list<T,Compare,Allocator> &other)
{
    not_implemented_yet();
}

//==============================================================================
// non-members

template <class T, class Compare, class Allocator>
inline
bool operator==(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs)
{
    not_implemented_yet();
    return false;
}

template <class T, class Compare, class Allocator>
inline
bool operator!=(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs)
{
    return !operator=(lhs, rhs);
}

template <class T, class Compare, class Allocator>
inline
bool operator<(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs)
{
    not_implemented_yet();
    return false;
}

template <class T, class Compare, class Allocator>
inline
bool operator<=(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs)
{
    not_implemented_yet();
    return false;
}

template <class T, class Compare, class Allocator>
inline
bool operator>(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs)
{
    not_implemented_yet();
    return false;
}

template <class T, class Compare, class Allocator>
inline
bool operator>=(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs)
{
    not_implemented_yet();
    return false;
}

template <class T, class Compare, class Allocator>
inline
void std::swap(skip_list<T,Compare,Allocator> &lhs, skip_list<T,Compare,Allocator> &rhs)
{
    lhs.swap(rhs);
}

//==============================================================================
// internal

template <class T, class Compare, class Allocator>
inline
unsigned skip_list<T,Compare,Allocator>::random_level()
{
    // TODO: decide on a better approach
    return rand() % max_levels;
}
