#pragma once

class ClassB
{
public:
    virtual void print() const = 0;
    virtual ~ClassB()          = default;
};

class ClassB1 : public ClassB
{
public:
    ClassB1(int x);
    ClassB1(float y);

    void print() const override;

private:
    union
    {
        int   m_x;
        float m_y;
    };
    bool kind_float;
};

class ClassB2 : public ClassB
{
public:
    ClassB2(double x);

    void print() const override;

private:
    double m_x;
};
