#pragma once
#include "subject.h"

#include <print>
#include <string_view>
#include <unordered_set>

class Observer
{
public:
    virtual ~Observer();

    template<typename T>
    class Update
    {
    public:
        virtual ~Update() = default;
        virtual void update(T& subject);

        virtual std::string_view name() const = 0;
    };
    using Compatibility = bool;
    Compatibility update(auto& subject);

    virtual std::string_view name() const = 0;

    void attachTo(Subject& subject);
    void detachFrom(Subject& subject);

private:
    friend class Subject;

    void notice(Subject& subject);
    void forget(Subject& subject);
    void forget(Subject& subject, struct no_print*);

private:
    std::unordered_set<Subject*> m_subjects;
};

Observer::Compatibility Observer::update(auto& subject)
{
    using SubjectT = std::remove_cvref_t<decltype(subject)>;
    auto* update   = dynamic_cast<Update<SubjectT>*>(this);

    if (update)
    {
        update->update(subject);
        return true;
    }
    else
    {
        std::println("    {}::update({}): incompatible", name(), subject.name());
        return false;
    }
};

template<typename T>
void Observer::Update<T>::update(T& subject) //
{
    std::println("    {}::update({}): not yet implemented", dynamic_cast<Observer*>(this)->name(), subject.name());
}
