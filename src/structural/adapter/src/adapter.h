#pragma once

#include "adaptee.h"
#include "object.h"

#include <memory>

class ObjectAdapterView : public IObject
{
public:
    ObjectAdapterView(Adaptee& adaptee)
            : m_adaptee{adaptee}
    {
    }

    void setData(const int a) override { m_adaptee.setData(a, a); }
    void print() const override { m_adaptee.display(); }

private:
    Adaptee& m_adaptee;
};

class ClassAdapter : public IObject,
                     private Adaptee
{
public:
    void setData(const int a) override { Adaptee::setData(a, a); }
    void print() const override { Adaptee::display(); }
};
