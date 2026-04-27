#include "variable_printer.h"
//
#include "../state_visitor.h"
#include "../states/state_initializing.h"
#include "../states/state_ready.h"

#include <memory>
#include <print>

using namespace std::string_view_literals;

class VariablePrinter::StateVisitor : public ::StateVisitor,
                                      public StateVisitorT<StateInitializing>,
                                      public StateVisitorT<StateReady>
{
public:
    StateVisitor(VariablePrinter& printer)
            : m_printer{printer}
    {
    }

    constexpr std::string_view visitorName() const override { return "VariablePrinter::StateVisitor"sv; }

    void visit(StateInitializing& state) override //
    {
        std::println("\nVariablePrinter is initializing.");
    }

    void visit(StateReady& state) override
    {
        if (!isReady)
        {
            state.init(m_printer.m_count, *this);
            std::println("\nVariablePrinter is ready.");
            isReady = true;
        }

        const auto                value    = state.value();
        constexpr decltype(value) maxValue = 48;

        if (value < maxValue)
            std::println("\nVariablePrinter: {}", value);
        else
        {
            std::println("\nVariablePrinter: value out of range ({})", value);
            state.stop();
        }
    }

private:
    VariablePrinter& m_printer;
    bool             isReady = false;
};

VariablePrinter::VariablePrinter(const int count)
        : Printer(std::make_unique<StateInitializing>(), std::make_unique<StateVisitor>(*this))
        , m_count{count}
{
}

void VariablePrinter::print()
{
    updateState();
}

void VariablePrinter::updateState()
{
    m_state->accept(*m_stateVisitor);
    auto newState = m_state->update();
    if (newState)
        m_state = std::move(newState);
}
