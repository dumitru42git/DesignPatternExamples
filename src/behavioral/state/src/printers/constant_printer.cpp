#include "constant_printer.h"
//
#include "../state_visitor.h"
#include "../states/state_finished.h"
#include "../states/state_initializing.h"
#include "../states/state_ready.h"

#include <memory>
#include <print>

using namespace std::string_view_literals;

class ConstantPrinter::InitStateVisitor : public ::StateVisitor,
                                          public StateVisitorT<StateReady>,
                                          public StateVisitorT<StateFinished>

{
public:
    InitStateVisitor(ConstantPrinter& printer)
            : m_printer{printer}
    {
    }

    constexpr std::string_view visitorName() const override { return "ConstantPrinter::InitStateVisitor"sv; }

    void visit(StateReady& state) override { state.init(m_printer.m_count, *this); }

    void visit(StateFinished& state) override
    {
        std::println("\nConstantPrinter is restarting.");
        state.restart();
        m_printer.m_isReady = false;
    }

private:
    ConstantPrinter& m_printer;
};

class ConstantPrinter::StateVisitor : public ::StateVisitor,
                                      public StateVisitorT<StateInitializing>
{
public:
    StateVisitor(ConstantPrinter& printer)
            : m_printer{printer}
    {
    }

    constexpr std::string_view visitorName() const override { return "ConstantPrinter::StateVisitor"sv; }

    void visit(StateInitializing& state) override
    {
        if (!m_printer.m_isReady)
        {
            state.skipComputation();
            std::println("\nConstantPrinter is initialized.");
            m_printer.m_isReady = true;
        }
    }

private:
    ConstantPrinter& m_printer;
};

ConstantPrinter::ConstantPrinter(const int value, const int count)
        : Printer(std::make_unique<StateInitializing>(), std::make_unique<StateVisitor>(*this))
        , m_initStateVisitor{std::make_unique<InitStateVisitor>(*this)}
        , m_value{value}
        , m_count{count}
        , m_isReady{false}
{
}

void ConstantPrinter::print()
{
    if (m_isReady)
    {
        std::println("\nConstantPrinter: {}", m_value);
    }

    updateState();
}

void ConstantPrinter::updateState()
{
    m_state->accept(*m_stateVisitor);
    auto newState = m_state->update();
    if (newState)
    {
        newState->accept(*m_initStateVisitor);
        m_state = std::move(newState);
    }
}
