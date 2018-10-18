/**
 *
 *  Row.h
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

#include <drogon/orm/Result.h>
#include <string>
namespace drogon
{
namespace orm
{
class Field;
class const_row_iterator;
class const_reverse_row_iterator;
class Row
{
  public:
    using size_type = unsigned long;
    using reference = Field;
    using const_iterator = const_row_iterator;
    using iterator = const_iterator;
    using const_reverse_iterator = const_reverse_row_iterator;

    using difference_type = long;

    reference operator[](size_type index) const;
    reference operator[](const char columnName[]) const;
    reference operator[](const std::string &columnName) const;
    size_type size() const;
    size_type capacity() const noexcept { return size(); }
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

  private:
    const Result &_result;

  protected:
    friend class Field;
    long _index = 0;
    size_t _end = 0;
    friend class Result;
    Row(const Result &r, size_type index) noexcept;
};
} // namespace orm
} // namespace drogon