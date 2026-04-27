#pragma once

#include "../printer.h"

class ConstantPrinter : public Printer
{
public:
    ConstantPrinter(int value, int count);

    void print() override;

private:
    void updateState();

private:
    class StateVisitor;
    class InitStateVisitor;

    std::unique_ptr<InitStateVisitor> m_initStateVisitor;

private:
    int  m_value;
    int  m_count;
    bool m_isReady;
};
