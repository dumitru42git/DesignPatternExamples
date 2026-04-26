#include "observer.h"
//
#include "subject.h"

#include <print>

Observer::~Observer()
{
    std::print("Observer::~Observer()");
    for (auto& subject : m_subjects)
    {
        std::print(" -> {}::forget()", subject->name());
        subject->forget(*this, (no_print*)nullptr);
    }
    std::println();
}

void Observer::attachTo(Subject& subject)
{
    auto [it, success] = m_subjects.insert(&subject);
    if (success)
    {
        std::print("{}::attachTo({})", name(), subject.name());
        subject.notice(*this);
    }
    else
    {
        std::println("{}::attachTo({}): already attached", name(), subject.name());
    }
}

void Observer::detachFrom(Subject& subject)
{
    if (m_subjects.erase(&subject))
    {
        std::print("{}::detachFrom({})", name(), subject.name());
        subject.forget(*this);
    }
    else
    {
        std::println("{}::detachFrom({}): not attached", name(), subject.name());
    }
}

void Observer::notice(Subject& subject)
{
    std::println(" -> {}::notice({})", name(), subject.name());
    m_subjects.insert(&subject);
}

void Observer::forget(Subject& subject)
{
    std::println(" -> {}::forget({})", name(), subject.name());
    m_subjects.erase(&subject);
}

void Observer::forget(Subject& subject, struct no_print*)
{
    m_subjects.erase(&subject);
}
