#pragma once

#include <print>

class Adaptee
{
public:
    void setData(const int a, const int b)
    {
        m_a = a;
        m_b = b;
    }

    void display() const { std::println("m_a = {}, m_b = {}", m_a, m_b); }

private:
    int m_a{}, m_b{};
};
