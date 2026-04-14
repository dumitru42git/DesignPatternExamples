#include "classB.h"

#include <print>

// ClassB1

ClassB1::ClassB1(int x)
        : m_x{x}
        , kind_float{false}
{
}

ClassB1::ClassB1(float y)
        : m_y{y}
        , kind_float{true}
{
}

void ClassB1::print()
{
    std::println("ClassB1::print() -> either x or y = {}", kind_float ? m_y : m_x);
}

// ClassB2

ClassB2::ClassB2(double x)
        : m_x{x}
{
}

void ClassB2::print()
{
    std::println("ClassB2::print() -> x = {}", m_x);
}
