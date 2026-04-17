#include "class.h"

#include <print>

// ClassA

ClassA::ClassA(int x, int y)
        : m_x{x}
        , m_y{y}
{
}

void ClassA::reset()
{
    m_x = {};
    m_y = {};
}

void ClassA::print() const
{
    std::println("ClassA::print() -> x = {}, y = {}", m_x, m_y);
}

std::unique_ptr<Class> ClassA::clone() const
{
    return std::make_unique<ClassA>(*this);
}

// ClassB

ClassB::ClassB(double x)
        : m_x{x}
{
}

void ClassB::reset()
{
    m_x = {};
}

void ClassB::print() const
{
    std::println("ClassB::print() -> x = {}", m_x);
}

std::unique_ptr<Class> ClassB::clone() const
{
    return std::make_unique<ClassB>(*this);
}
