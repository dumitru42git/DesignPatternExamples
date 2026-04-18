#pragma once

#include "class.h"

#include <memory>
#include <print>
#include <vector>

class SimpleClass : public Class
{
public:
    SimpleClass(int data)
            : m_data{data}
    {
    }

    void print(const int indent = 0, const int spaces = 4) const override
    { //
        Class::print(indent, spaces);
        std::println("SimpleClass: m_data = {}", m_data);
    }

private:
    int m_data;
};