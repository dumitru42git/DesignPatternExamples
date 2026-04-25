#pragma once

#include <memory>
#include <string_view>

class Implementation
{
public:
    virtual void print(std::string_view callerName) const = 0;
    virtual void setData(int data)                        = 0;

    std::unique_ptr<Implementation> clone() const;

    virtual ~Implementation() = default;

private:
    virtual Implementation* cloneImpl() const = 0;
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

    std::unique_ptr<ImplementationA> clone() const;

private:
    virtual ImplementationA* cloneImpl() const override;

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

    std::unique_ptr<ImplementationB> clone() const;

private:
    virtual ImplementationB* cloneImpl() const override;

private:
    int m_x;
    int m_y;
};
