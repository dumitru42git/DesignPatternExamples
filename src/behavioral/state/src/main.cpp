#include "printers/constant_printer.h"
#include "printers/variable_printer.h"

#include <chrono>
#include <memory>
#include <print>
#include <thread>

using namespace std::chrono_literals;

int main()
{
    std::println("---State Pattern---");

    int                      count           = 10;
    std::unique_ptr<Printer> variablePrinter = std::make_unique<VariablePrinter>(count);
    for (int i = 0; i < 6; i++)
    {
        variablePrinter->print();
        std::this_thread::sleep_for(600ms);
    }
    for (int i = 0; i < 6; i++)
    {
        variablePrinter->print();
    }
    std::println("\n-----------------------------------------------------------------");

    count                                    = 4;
    std::unique_ptr<Printer> constantPrinter = std::make_unique<ConstantPrinter>(42, count);
    for (int i = 0; i < 6; i++)
    {
        constantPrinter->print();
        std::this_thread::sleep_for(100ms);
    }
    for (int i = 0; i < 6; i++)
    {
        constantPrinter->print();
    }
    std::println("\n-----------------------------------------------------------------");

    return 0;
}
