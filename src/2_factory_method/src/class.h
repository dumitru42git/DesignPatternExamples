#pragma once

class Class
{
public:
    virtual void func() = 0;
    virtual ~Class()     = default;
};

class ClassA : public Class
{
public:
    ClassA(int x, int y);

    void func() override;

private:
    int m_x;
    int m_y;
};

class ClassB : public Class
{
public:
    ClassB(int x);
    ClassB(float y);

    void func() override;

private:
    union
    {
        int   m_x;
        float m_y;
    };
    bool kind_float;
};
