#pragma once

#include "../printer.h"

class VariablePrinter : public Printer
{
public:
    VariablePrinter(int count);

    void print() override;

private:
    void updateState();

private:
    class StateVisitor;

private:
    int m_count;
};
