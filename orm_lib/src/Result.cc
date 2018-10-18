#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/ResultIterator.h>
#include <assert.h>
using namespace drogon::orm;

Result::const_iterator Result::begin() const noexcept
{
    return const_iterator(*this, (size_type)0);
}
Result::const_iterator Result::cbegin() const noexcept
{
    return begin();
}
Result::const_iterator Result::end() const noexcept
{
    return const_iterator(*this, size());
}
Result::const_iterator Result::cend() const noexcept
{
    return end();
}

Result::const_reverse_iterator Result::rbegin() const
{
    return const_reverse_result_iterator(end());
}
Result::const_reverse_iterator Result::crbegin() const
{
    return rbegin();
}
Result::const_reverse_iterator Result::rend() const
{
    return const_reverse_result_iterator(begin());
}
Result::const_reverse_iterator Result::crend() const
{
    return rend();
}

Result::const_iterator Result::const_reverse_iterator::base() const noexcept
{
    iterator_type tmp(*this);
    return ++tmp;
}

Result::reference Result::front() const noexcept
{
    return Row(*this, 0);
}

Result::reference Result::back() const noexcept
{
    return Row(*this, size() - 1);
}

Result::reference Result::operator[](size_type index) const
{
    assert(index < size());
    return Row(*this, index);
}
Result::reference Result::at(size_type index) const
{
    return operator[](index);
}

const_result_iterator const_result_iterator::operator++(int)
{
    const_result_iterator old(*this);
    _index++;
    return old;
}
const_result_iterator const_result_iterator::operator--(int)
{
    const_result_iterator old(*this);
    _index--;
    return old;
}

const_reverse_result_iterator const_reverse_result_iterator::operator++(int)
{
    const_reverse_result_iterator old(*this);
    iterator_type::operator--();
    return old;
}

const_reverse_result_iterator const_reverse_result_iterator::operator--(int)
{
    const_reverse_result_iterator old(*this);
    iterator_type::operator++();
    return old;
}
