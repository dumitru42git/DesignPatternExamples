#pragma once

#include <string_view>

class Implementation
{
public:
    virtual void print(std::string_view callerName) const = 0;
    virtual void setData(int data)                        = 0;

    virtual ~Implementation();
};

class ImplementationA : public Implementation
{
public:
    ImplementationA(int data)
            : m_data{data}
    {
    }

    void print(std::string_view callerName) const override;
    void setData(int data) override;

private:
    int m_data;
};

class ImplementationB : public Implementation
{
public:
    ImplementationB(int data)
            : m_x{data}
            , m_y{data}
    {
    }

    void print(std::string_view callerName) const override;
    void setData(int data) override;

private:
    int m_x;
    int m_y;
};
