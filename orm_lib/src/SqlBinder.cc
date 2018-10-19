/**
 *
 *  SqlBinder.cc
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *
 */

#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/DbClient.h>
#include <stdio.h>
#include <future>
#include <iostream>
using namespace drogon::orm;
using namespace drogon::orm::internal;

SqlBinder::~SqlBinder()
{
    auto holder = _callbackHolder;
    if (_mode == Mode::Async)
    {
        //async mode,default mode
        _client.execSql(_sql, _paraNum, _parameters, _length, _format,
                        [holder](const Result &r) {
                            if (holder)
                            {
                                holder->execCallback(r);
                            }
                        });
    }
    else
    {
        //sync mode
        std::promise<Result> pro;
        auto f = pro.get_future();
        _client.execSql(_sql, _paraNum, _parameters, _length, _format,
                        [&pro](const Result &r) {
                            pro.set_value(r);
                        });
        if (holder)
            holder->execCallback(f.get());
    }
}
