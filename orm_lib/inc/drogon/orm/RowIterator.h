/**
 *
 *  RowIterator.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  @section DESCRIPTION
 *
 */

#pragma once

#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
namespace drogon
{
namespace orm
{
class const_row_iterator : public std::iterator<
                               std::random_access_iterator_tag,
                               const Field,
                               Row::difference_type,
                               const_row_iterator,
                               Field>,
                           protected Field
{
  public:
    using pointer = const Field *;
    using reference = Field;
    using size_type = Row::size_type;
    using difference_type = Row::difference_type;
    //const_row_iterator(const Field &t) noexcept : Field(t) {}

    pointer operator->() { return this; }
    reference operator*() { return Field(*this); }

    const_row_iterator operator++(int);
    const_row_iterator &operator++()
    {
        ++_column;
        return *this;
    }
    const_row_iterator operator--(int);
    const_row_iterator &operator--()
    {
        --_column;
        return *this;
    }
    const_row_iterator &operator+=(difference_type i)
    {
        _column += i;
        return *this;
    }
    const_row_iterator &operator-=(difference_type i)
    {
        _column -= i;
        return *this;
    }

    bool operator==(const const_row_iterator &other) const
    {
        return _column == other._column;
    }
    bool operator!=(const const_row_iterator &other) const
    {
        return _column != other._column;
    }
    bool operator>(const const_row_iterator &other) const
    {
        return _column > other._column;
    }
    bool operator<(const const_row_iterator &other) const
    {
        return _column < other._column;
    }
    bool operator>=(const const_row_iterator &other) const
    {
        return _column >= other._column;
    }
    bool operator<=(const const_row_iterator &other) const
    {
        return _column <= other._column;
    }

  private:
    friend class Row;
    const_row_iterator(const Row &r, size_type column) noexcept : Field(r, column) {}
};

class const_reverse_row_iterator : private const_row_iterator
{
  public:
    using super = const_row_iterator;
    using iterator_type = const_row_iterator;
    using iterator_type::difference_type;
    using iterator_type::iterator_category;
    using iterator_type::pointer;
    using value_type = iterator_type::value_type;
    using reference = iterator_type::reference;

    const_reverse_row_iterator(
        const const_reverse_row_iterator &rhs) : const_row_iterator(rhs) {}
    explicit const_reverse_row_iterator(
        const const_row_iterator &rhs) : const_row_iterator(rhs) { super::operator--(); }

    const_row_iterator base() const noexcept;

    using iterator_type::operator->;
    using iterator_type::operator*;

    const_reverse_row_iterator operator++(int);
    const_reverse_row_iterator &operator++()
    {
        iterator_type::operator--();
        return *this;
    }
    const_reverse_row_iterator operator--(int);
    const_reverse_row_iterator &operator--()
    {
        iterator_type::operator++();
        return *this;
    }
    const_reverse_row_iterator &operator+=(difference_type i)
    {
        iterator_type::operator-=(i);
        return *this;
    }
    const_reverse_row_iterator &operator-=(difference_type i)
    {
        iterator_type::operator+=(i);
        return *this;
    }

    bool operator==(const const_reverse_row_iterator &other) const
    {
        return _column == other._column;
    }
    bool operator!=(const const_reverse_row_iterator &other) const
    {
        return _column != other._column;
    }
    bool operator>(const const_reverse_row_iterator &other) const
    {
        return _column < other._column;
    }
    bool operator<(const const_reverse_row_iterator &other) const
    {
        return _column > other._column;
    }
    bool operator>=(const const_reverse_row_iterator &other) const
    {
        return _column <= other._column;
    }
    bool operator<=(const const_reverse_row_iterator &other) const
    {
        return _column >= other._column;
    }
};

} // namespace orm
} // namespace drogon