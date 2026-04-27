#pragma once

#include "../state.h"

class StateFinished : public State
{
public:
    void                   accept(StateVisitor& rawVisitor) override;
    std::unique_ptr<State> update() override;
    void                   print() const override;

    void restart();

private:
    bool m_shouldRestart;
};
