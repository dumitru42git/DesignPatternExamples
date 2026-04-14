#include "classA.h"

#include <print>

// ClassA1

ClassA1::ClassA1(int x, int y)
        : m_x{x}
        , m_y{y}
{
}

void ClassA1::print()
{
    std::println("ClassA1::print() -> x = {}, y = {}", m_x, m_y);
}

// ClassA2

ClassA2::ClassA2(double x, double y)
        : m_x{x}
        , m_y{y}
{
}

void ClassA2::print()
{
    std::println("ClassA2::print() -> x = {}, y = {}", m_x, m_y);
}
