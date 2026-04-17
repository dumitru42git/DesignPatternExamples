#pragma once

class Class
{
public:
    virtual void print() = 0;
    virtual ~Class()    = default;
};

class ClassA : public Class
{
public:
    void print() override;

private:
    friend class BuilderA;
    ClassA(int x, int y);

private:
    int m_x;
    int m_y;
};

class ClassB : public Class
{
public:
    void print() override;

private:
    friend class BuilderB;
    ClassB(double x);

private:
    double m_x;
};
