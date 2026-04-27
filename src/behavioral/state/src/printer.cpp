#include "printer.h"

Printer::Printer(std::unique_ptr<State> state, std::unique_ptr<StateVisitor> stateVisitor)
        : m_state{std::move(state)}
        , m_stateVisitor{std::move(stateVisitor)}
{
}
