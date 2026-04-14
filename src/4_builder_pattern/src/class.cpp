#include "class.h"

#include <print>

// ClassA

ClassA::ClassA(int x, int y)
        : m_x{x}
        , m_y{y}
{
}

void ClassA::print()
{
    std::println("ClassA::print() -> x = {}, y = {}", m_x, m_y);
}

// ClassB

ClassB::ClassB(double x)
        : m_x{x}
{
}

void ClassB::print()
{
    std::println("ClassB::print() -> x = {}", m_x);
}
