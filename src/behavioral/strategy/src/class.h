#pragma once

#include "print.h"

#include <list>
#include <memory>
#include <print>
#include <set>
#include <vector>

class ConstexprClass
{
public:
    constexpr ConstexprClass(std::vector<int> vecInt, std::vector<double> vecDouble, std::unique_ptr<Print> printStrategy)
            : m_vecInt{std::move(vecInt)}
            , m_vecDouble{std::move(vecDouble)}
            , m_printStrategy{std::move(printStrategy)}
    {
    }

    constexpr void print() const
    {
        if (!std::is_constant_evaluated())
            std::print("ConstexprClass::vecInt: ");
        (*m_printStrategy)(m_vecInt);

        if (!std::is_constant_evaluated())
            std::print("ConstexprClass::vecDouble: ");
        (*m_printStrategy)(m_vecDouble);
    }

protected:
    std::vector<int>       m_vecInt;
    std::vector<double>    m_vecDouble;
    std::unique_ptr<Print> m_printStrategy;
};

class Class : public ConstexprClass
{
public:
    Class(std::vector<int>       vecInt,
          std::vector<double>    vecDouble,
          std::list<float>       listFloat,
          std::set<int>          setInt,
          std::unique_ptr<Print> printStrategy //
          )
            : ConstexprClass(std::move(vecInt), std::move(vecDouble), std::move(printStrategy))
            , m_listFloat{std::move(listFloat)}
            , m_setInt{std::move(setInt)}
    {
    }

    void print() const
    {
        ConstexprClass::print();
        std::print("Class::listFloat: "), (*m_printStrategy)(m_listFloat);
        std::print("Class::setInt: "), (*m_printStrategy)(m_setInt);
    }

protected:
    std::list<float> m_listFloat;
    std::set<int>    m_setInt;
};
