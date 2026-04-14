#include "builder.h"

// BuilderA

void BuilderA::buildX(const Json& json)
{
    auto it = json.find("x");
    if (it != json.end())
    {
        m_x = it->get<int>();
    }
}

void BuilderA::buildY(const Json& json)
{
    auto it = json.find("y");
    if (it != json.end())
    {
        m_y = it->get<int>();
    }
}

std::unique_ptr<Class> BuilderA::getResult() const
{
    return std::unique_ptr<Class>(new ClassA(m_x, m_y));
}

// BuilderB

void BuilderB::buildX(const Json& json)
{
    auto it = json.find("x1");
    if (it != json.end())
    {
        m_x += it->get<double>();
    }
    it = json.find("x2");
    if (it != json.end())
    {
        m_x += it->get<double>();
    }
}

std::unique_ptr<Class> BuilderB::getResult() const
{
    return std::unique_ptr<Class>(new ClassB(m_x));
}
