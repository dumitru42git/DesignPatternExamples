#pragma once

#include <print>

class IObject
{
public:
    virtual void setData(int a) = 0;
    virtual void print() const  = 0;

    virtual ~IObject() = default;
};

class ConcreteObject : public IObject
{
    void setData(const int a) override { m_a = a; }
    void print() const override { std::println("m_a = {}", m_a); }

private:
    int m_a{};
};
