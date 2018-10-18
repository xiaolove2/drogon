#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/RowIterator.h>
using namespace drogon::orm;
Row::Row(const Result &r,size_type index) noexcept :
_result(r),
_index(long(index)),
_end(r.columns())
{

}
Row::size_type Row::size() const
{
    return _end;
}
Row::reference Row::operator[](size_type index) const
{
    if(index>=_end)
        throw;//TODO throw....
    return Field(*this,index);
}

Row::reference Row::operator[](const char columnName[]) const
{
    auto N=_result.columnNumber(columnName);
    return Field(*this,N);
}

Row::reference Row::operator[](const std::string &columnName) const{
    return operator[](columnName.c_str());
}

Row::const_iterator Row::begin() const noexcept {
    return const_iterator(*this,0);
}
Row::const_iterator Row::cbegin() const noexcept {
    return begin();
}
Row::const_iterator Row::end() const noexcept {
    return const_iterator(*this,size());
}

Row::const_iterator Row::cend() const noexcept {
    return end();
}

Row::const_reverse_iterator Row::rbegin() const
{
    return const_reverse_row_iterator(end());
}
Row::const_reverse_iterator Row::crbegin() const
{
    return rbegin();
}
Row::const_reverse_iterator Row::rend() const
{
    return const_reverse_row_iterator(begin());
}
Row::const_reverse_iterator Row::crend() const
{
    return rend();
}
Row::const_iterator Row::const_reverse_iterator::base() const noexcept
{
    iterator_type tmp(*this);
    return ++tmp;
}

const_row_iterator const_row_iterator::operator++(int) {
    const_row_iterator old(*this);
    _column++;
    return old;
}
const_row_iterator const_row_iterator::operator--(int) {
    const_row_iterator old(*this);
    _column--;
    return old;
}

const_reverse_row_iterator const_reverse_row_iterator::operator++(int) {
    const_reverse_row_iterator old(*this);
    iterator_type::operator--();
    return old;
}
const_reverse_row_iterator const_reverse_row_iterator::operator--(int) {
    const_reverse_row_iterator old(*this);
    iterator_type::operator++();
    return old;
}
