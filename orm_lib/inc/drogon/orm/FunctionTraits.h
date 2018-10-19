/**
 *
 *  FunctionTraits.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *
 */

#pragma once
#include <tuple>
#include <type_traits>
#include <string>
namespace drogon
{
namespace orm
{

enum class SqlStatus;
class Result;
namespace internal
{

template <typename>
struct FunctionTraits;
template <>
struct FunctionTraits<void (*)()>
{
        typedef void result_type;
        template <std::size_t Index>
        using argument = void;
        static const std::size_t arity = 0;

        static const bool isSqlCallback = false;
};
//functor,lambda
template <typename Function>
struct FunctionTraits : public FunctionTraits<
                            decltype(&std::remove_reference<Function>::type::operator())>
{
};

template <
    typename ClassType,
    typename ReturnType,
    typename... Arguments>
struct FunctionTraits<
    ReturnType (ClassType::*)(Arguments...) const> : FunctionTraits<ReturnType (*)(Arguments...)>
{
        static const std::string name() { return std::string("Class Function"); }
};

/* support the non-const operator ()
         * this will work with user defined functors */
template <
    typename ClassType,
    typename ReturnType,
    typename... Arguments>
struct FunctionTraits<
    ReturnType (ClassType::*)(Arguments...)> : FunctionTraits<ReturnType (*)(Arguments...)>
{
        typedef ClassType class_type;
        static const std::string name() { return std::string("Class Function"); }
};

template <>
struct FunctionTraits<void (*)(const Result &)>
    : public FunctionTraits<void (*)()>
{
        static const bool isSqlCallback = true;
        static const bool isStepResultCallback = false;
};
//normal function
template <
    typename ReturnType,
    typename... Arguments>
struct FunctionTraits<
    ReturnType (*)(const SqlStatus, Arguments...)> : FunctionTraits<ReturnType (*)(Arguments...)>
{
        static const bool isSqlCallback = true;
        static const bool isStepResultCallback = true;
};

template <
    typename ReturnType,
    typename... Arguments>
struct FunctionTraits<
    ReturnType (*)(Arguments...)>
{
        typedef ReturnType result_type;

        template <std::size_t Index>
        using argument = typename std::tuple_element<
            Index,
            std::tuple<Arguments...>>::type;

        static const std::size_t arity = sizeof...(Arguments);

        static const bool isSqlCallback = false;
};
} // namespace internal
} // namespace orm
} // namespace drogon