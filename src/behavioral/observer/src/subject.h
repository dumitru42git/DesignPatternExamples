#pragma once

#include <string_view>
#include <unordered_set>

class Observer;

class Subject
{
public:
    virtual ~Subject();

    virtual void             notify()     = 0;
    virtual std::string_view name() const = 0;

    void attach(Observer& observer);
    void detach(Observer& observer);

protected:
    using Observers = std::unordered_set<Observer*>;

    void                notify(auto& subject);
    Observers::iterator detach(Observers::iterator it);

private:
    friend class Observer;

    void notice(Observer& observer);
    void forget(Observer& observer);
    void forget(Observer& observer, struct no_print*);

protected:
    Observers m_observers;
};
