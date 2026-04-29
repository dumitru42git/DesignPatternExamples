#pragma once

#include <cmath>
#include <print>

class TemplateMethod
{
public:
    TemplateMethod(unsigned int data)
            : m_data{data}
    {
    }
    virtual ~TemplateMethod() = default;

    virtual void update() = 0;
    void         method()
    {
        update();
        print();
    }

protected:
    void print() { std::println("data = {}", m_data); }

protected:
    unsigned int m_data;
};

class TemplateMethodSquare : public TemplateMethod
{
    using TemplateMethod::TemplateMethod;
    void update() override { m_data *= m_data; }
};

class TemplateMethodExp : public TemplateMethod
{
    using TemplateMethod::TemplateMethod;
    void update() override { m_data = std::exp(m_data); }
};
