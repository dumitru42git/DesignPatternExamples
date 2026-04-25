#include "interface.h"
//
#include "../private/implementation.h"

template<typename ImplementationT>
std::unique_ptr<Interface> Interface::create(int data)
{
    auto object = std::make_unique<Interface>();
    object->m_impl.reset(new ImplementationT(data));
    return object;
}

template std::unique_ptr<Interface> Interface::create<ImplementationA>(int);
template std::unique_ptr<Interface> Interface::create<ImplementationB>(int);

void Interface::print() const
{
    if (m_impl)
        m_impl->print("Interface");
}

Interface::Memento Interface::save() const
{
    return Interface::Memento(m_impl->clone().release());
}

void Interface::load(Interface::Memento memento)
{
    m_impl = std::move(memento);
}

Interface::~Interface() = default;
