#pragma once

#include <format>
#include <string>

class Class
{
public:
    virtual [[nodiscard]] std::string printString() const = 0;
    virtual int                       getId() const       = 0;
    virtual ~Class()                                      = default;
};

class ClassA : public Class
{
public:
    ClassA(int id, int x)
            : m_id{id}
            , m_x{x}
    {
    }

    [[nodiscard]] std::string printString() const override //
    {
        return std::format("m_x = {}", m_x);
    }

    int getId() const override { return m_id; }

private:
    int m_id{};
    int m_x{};
};
