/**
 *
 *  Result.h
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

#include <memory>
#include <string>
#ifdef _WIN32
#define noexcept _NOEXCEPT
#endif
namespace drogon
{
namespace orm
{
class const_result_iterator;
class const_reverse_result_iterator;
class Row;
enum class SqlStatus
{
    Ok,
    NetworkError,
    Busy,
    SqlError,
    End
};
class Result
{
  public:
    using difference_type = long;
    using size_type = unsigned long;
    using reference = Row;
    using const_iterator = const_result_iterator;
    using iterator = const_iterator;
    using row_size_type = unsigned long;
    using field_size_type = unsigned long;

    using const_reverse_iterator = const_reverse_result_iterator;
    using reverse_iterator = const_reverse_iterator;

    virtual size_type size() const noexcept = 0;
    size_type capacity() const noexcept { return size(); }
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    virtual bool empty() const noexcept = 0;

    reference front() const noexcept;
    reference back() const noexcept;

    reference operator[](size_type index) const;
    reference at(size_type index) const;
    /// swap with another object
    virtual void swap(Result &) noexcept = 0;
    ///number of columns in result;
    virtual row_size_type columns() const noexcept = 0;
    /// Name of column with this number (throws exception if it doesn't exist)
    virtual const char *columnName(row_size_type Number) const = 0;

    // const SqlStatus status() const { return _status; }
    const std::string &errorDescription() const { return _errString; }
    void setError(const std::string &description) { _errString = description; }

    virtual size_type affectedRows() const noexcept = 0;

  private:
    std::string _query;

    std::string _errString;
    friend class Field;
    friend class Row;
    /// Number of given column (throws exception if it doesn't exist).
    virtual row_size_type columnNumber(const char colName[]) const = 0;
    /// Number of given column (throws exception if it doesn't exist).
    row_size_type columnNumber(const std::string &name) const
    {
        return columnNumber(name.c_str());
    }

    virtual const char *getValue(size_type row, row_size_type colum) const = 0;
    virtual bool isNull(size_type row, row_size_type colum) const = 0;
    virtual field_size_type getLength(size_type row, row_size_type colum) const = 0;
    // friend Result makeResult(SqlStatus status, const std::shared_ptr<PGresult> &r, const std::string &query);
    // Result(SqlStatus status, const std::shared_ptr<PGresult> &r, const std::string &query) noexcept;
    Result() = default;
};
} // namespace orm
} // namespace drogon