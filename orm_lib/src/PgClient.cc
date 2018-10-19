
/**
 *
 *  PgClient.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Implementation of the drogon::orm::PgClient class.
 * 
 */

#include <drogon/orm/PgClient.h>

using namespace drogon::orm;

void PgClient::execSql(const std::string &sql,
                       size_t paraNum,
                       const std::vector<const char *> &parameters,
                       const std::vector<int> &length,
                       const std::vector<int> &format,
                       const QueryCallback &cb)
{
}