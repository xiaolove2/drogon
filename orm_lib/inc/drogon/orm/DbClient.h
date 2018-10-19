/**
 *
 *  DbClient.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *
 */

#pragma once
#include <trantor/utils/NonCopyable.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Result.h>
#include <string>
#include <functional>

namespace drogon
{
namespace orm
{

typedef std::function<void(const Result &)> QueryCallback;

enum class DbType
{
    MySql,
    PostgreSQL,
    Oracle,
    Odbc
};

class DbClient : public trantor::NonCopyable
{
  public:
    static DbClient &createDbClient(const std::string &connInfo, const size_t connnectionsNum, DbType type);

    virtual ~DbClient(){};
    internal::SqlBinder operator<<(const std::string &sql);

  private:
    friend internal::SqlBinder;
    virtual void execSql(const std::string &sql,
                         size_t paraNum,
                         const std::vector<const char *> &parameters,
                         const std::vector<int> &length,
                         const std::vector<int> &format,
                         const QueryCallback &cb) = 0;
};

} // namespace orm
} // namespace drogon