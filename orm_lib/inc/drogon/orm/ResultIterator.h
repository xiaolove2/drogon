#pragma once

#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
namespace drogon
{
namespace orm
{
class const_result_iterator : public std::iterator<
                                  std::random_access_iterator_tag,
                                  const Row,
                                  Result::difference_type,
                                  const_result_iterator,
                                  Row>,
                              protected Row
{
  public:
    using pointer = const Row *;
    using reference = Row;
    using size_type = Result::size_type;
    using difference_type = Result::difference_type;
    //const_result_iterator(const Row &t) noexcept : Row(t) {}

    pointer operator->() { return this; }
    reference operator*() { return Row(*this); }

    const_result_iterator operator++(int);
    const_result_iterator &operator++()
    {
        ++_index;
        return *this;
    }
    const_result_iterator operator--(int);
    const_result_iterator &operator--()
    {
        --_index;
        return *this;
    }
    const_result_iterator &operator+=(difference_type i)
    {
        _index += i;
        return *this;
    }
    const_result_iterator &operator-=(difference_type i)
    {
        _index -= i;
        return *this;
    }

    bool operator==(const const_result_iterator &other) const
    {
        return _index == other._index;
    }
    bool operator!=(const const_result_iterator &other) const
    {
        return _index != other._index;
    }
    bool operator>(const const_result_iterator &other) const
    {
        return _index > other._index;
    }
    bool operator<(const const_result_iterator &other) const
    {
        return _index < other._index;
    }
    bool operator>=(const const_result_iterator &other) const
    {
        return _index >= other._index;
    }
    bool operator<=(const const_result_iterator &other) const
    {
        return _index <= other._index;
    }

  private:
    friend class Result;
    const_result_iterator(const Result &r, size_type index) noexcept : Row(r, index) {}
};

class const_reverse_result_iterator : private const_result_iterator
{
  public:
    using super = const_result_iterator;
    using iterator_type = const_result_iterator;
    using iterator_type::difference_type;
    using iterator_type::iterator_category;
    using iterator_type::pointer;
    using value_type = iterator_type::value_type;
    using reference = iterator_type::reference;

    const_reverse_result_iterator(
        const const_reverse_result_iterator &rhs) : const_result_iterator(rhs) {}
    explicit const_reverse_result_iterator(
        const const_result_iterator &rhs) : const_result_iterator(rhs) { super::operator--(); }

    const_result_iterator base() const noexcept;

    using iterator_type::operator->;
    using iterator_type::operator*;

    const_reverse_result_iterator operator++(int);
    const_reverse_result_iterator &operator++()
    {
        iterator_type::operator--();
        return *this;
    }
    const_reverse_result_iterator operator--(int);
    const_reverse_result_iterator &operator--()
    {
        iterator_type::operator++();
        return *this;
    }
    const_reverse_result_iterator &operator+=(difference_type i)
    {
        iterator_type::operator-=(i);
        return *this;
    }
    const_reverse_result_iterator &operator-=(difference_type i)
    {
        iterator_type::operator+=(i);
        return *this;
    }

    bool operator==(const const_reverse_result_iterator &other) const
    {
        return _index == other._index;
    }
    bool operator!=(const const_reverse_result_iterator &other) const
    {
        return _index != other._index;
    }
    bool operator>(const const_reverse_result_iterator &other) const
    {
        return _index < other._index;
    }
    bool operator<(const const_reverse_result_iterator &other) const
    {
        return _index > other._index;
    }
    bool operator>=(const const_reverse_result_iterator &other) const
    {
        return _index <= other._index;
    }
    bool operator<=(const const_reverse_result_iterator &other) const
    {
        return _index >= other._index;
    }
};

} // namespace orm
} // namespace drogon