#pragma once

#include "../state.h"

#include <future>
#include <optional>

class StateInitializing : public State
{
public:
    StateInitializing();

    void                   accept(StateVisitor& rawVisitor) override;
    std::unique_ptr<State> update() override;
    void                   print() const override;

    void skipComputation();

private:
    std::future<std::optional<int>> m_future;
    std::stop_source                m_stopSource;
    std::optional<int>              m_compResult;
};
