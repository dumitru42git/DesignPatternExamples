#pragma once

#include <print>

class Object
{
public:
    Object(int data)
            : m_data{data}
    {
    }

    void set(int data) { m_data = data; }
    int  get() const { return m_data; }
    void print() const { std::println("Object: m_data = {}", m_data); }

private:
    int m_data;
};
