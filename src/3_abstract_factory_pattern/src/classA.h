#pragma once

class ClassA
{
public:
    virtual void func() = 0;
    virtual ~ClassA()     = default;
};

class ClassA1 : public ClassA
{
public:
    ClassA1(int x, int y);

    void func() override;

private:
    int m_x;
    int m_y;
};

class ClassA2 : public ClassA
{
public:
    ClassA2(double x, double y);

    void func() override;

private:
    double m_x;
    double m_y;
};