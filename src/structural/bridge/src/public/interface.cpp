#include "interface.h"
//
#include "../private/implementation.h"

Interface::Interface(std::unique_ptr<Implementation, ImplementationDeleter> impl)
        : m_impl{std::move(impl)}
{
}

void Interface::print() const
{
    if (m_impl)
        m_impl->print("Interface");
}

Interface::~Interface() = default;

void ExtendedInterface::print() const
{
    if (m_impl)
        m_impl->print("ExtendedInterface");
}

void ExtendedInterface::reset()
{
    if (m_impl)
        m_impl->setData(0);
}
