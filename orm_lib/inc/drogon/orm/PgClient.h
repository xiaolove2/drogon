/**
 *
 *  PgClient.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Definitions for the PostgreSQL client class
 * 
 */

#include <drogon/orm/DbClient.h>

namespace drogon
{
namespace orm
{

class PgClient : public DbClient
{
  public:
    PgClient(const std::string &connInfo, const size_t connNum);

  private:
    virtual void execSql(const std::string &sql,
                         size_t paraNum,
                         const std::vector<const char *> &parameters,
                         const std::vector<int> &length,
                         const std::vector<int> &format,
                         const QueryCallback &cb) override;
};

} // namespace orm
} // namespace drogon