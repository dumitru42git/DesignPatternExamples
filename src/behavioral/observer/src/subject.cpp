#include "subject.h"
//
#include "observer.h"

#include <print>

Subject::~Subject()
{
    std::print("Subject::~Subject()");
    for (auto& observer : m_observers)
    {
        std::print(" -> {}::forget()", observer->name());
        observer->forget(*this, (no_print*)nullptr);
    }
    std::println();
}

void Subject::attach(Observer& observer)
{
    auto [it, success] = m_observers.insert(&observer);
    if (success)
    {
        std::print("{}::attach({})", name(), observer.name());
        observer.notice(*this);
    }
    else
    {
        std::println("{}::attach({}): already attached", name(), observer.name());
    }
}

void Subject::detach(Observer& observer)
{
    if (m_observers.erase(&observer))
    {
        std::print("{}::detach({})", name(), observer.name());
        observer.forget(*this);
    }
    else
    {
        std::println("{}::detach({}): not attached", name(), observer.name());
    }
}

Subject::Observers::iterator Subject::detach(Observers::iterator it)
{
    auto* const observer = *it;
    auto        next     = m_observers.erase(it);

    std::print("    {}::detach({})", name(), observer->name());

    observer->forget(*this);
    return next;
}

void Subject::notice(Observer& observer)
{
    std::println(" -> {}::notice({})", name(), observer.name());
    m_observers.insert(&observer);
}

void Subject::forget(Observer& observer)
{
    std::println(" -> {}::forget({})", name(), observer.name());
    forget(observer, nullptr);
}

void Subject::forget(Observer& observer, struct no_print*)
{
    m_observers.erase(&observer);
}
