#pragma once

#include "../state.h"

class StateReady : public State
{
public:
    StateReady(int value);
    void init(int count);
    void init(int count, StateVisitor& visitor);

    void                   accept(StateVisitor& visitor) override;
    std::unique_ptr<State> update() override;
    void                   print() const override;

    void stop();
    int  value() const;

private:
    int  m_value;
    int  m_count;
    int  m_index;
    bool m_shouldStop;
};
