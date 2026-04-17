#pragma once

class ClassA
{
public:
    virtual void print() const = 0;
    virtual ~ClassA()          = default;
};

class ClassA1 : public ClassA
{
public:
    ClassA1(int x, int y);

    void print() const override;

private:
    int m_x;
    int m_y;
};

class ClassA2 : public ClassA
{
public:
    ClassA2(double x, double y);

    void print() const override;

private:
    double m_x;
    double m_y;
};