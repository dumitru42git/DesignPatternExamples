#include "class.h"

#include <print>

ClassA::ClassA(int x, int y)
        : m_x{x}
        , m_y{y}
{
}

void ClassA::func()
{
    std::println("ClassA::func() -> x = {}, y = {}", m_x, m_y);
}

ClassB::ClassB(int x)
        : m_x{x}
        , kind_float{false}
{
}

ClassB::ClassB(float y)
        : m_y{y}
        , kind_float{true}
{
}

void ClassB::func()
{
    std::println("ClassB::func() -> either x or y = {}", kind_float ? m_y : m_x);
}
