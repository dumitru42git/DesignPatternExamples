#pragma once

#include <memory>

class Class
{
public:
    virtual void                   reset()       = 0;
    virtual void                   print() const = 0;
    virtual std::unique_ptr<Class> clone() const = 0;

    virtual ~Class() = default;
};

class ClassA : public Class
{
public:
    ClassA(int x, int y);

    void                   reset() override;
    void                   print() const override;
    std::unique_ptr<Class> clone() const override;

private:
    int m_x;
    int m_y;
};

class ClassB : public Class
{
public:
    ClassB(double x);

    void                   reset() override;
    void                   print() const override;
    std::unique_ptr<Class> clone() const override;

private:
    double m_x;
};
