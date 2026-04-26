#pragma once
#include <print>

void Subject::notify(auto& subject)
{
    for (auto it = m_observers.begin(); it != m_observers.end();)
    {
        auto*      observer   = *it;
        const bool compatible = observer->update(subject);

        if (!compatible)
            it = subject.detach(it);
        else
            ++it;
    }
}
