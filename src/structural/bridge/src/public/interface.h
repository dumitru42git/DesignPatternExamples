#pragma once

#include "implementation_factory.h"

#include <memory>

class Implementation;

class Interface
{
public:
    Interface(std::unique_ptr<Implementation, ImplementationDeleter> impl);

    virtual void print() const;
    virtual ~Interface();

protected:
    std::unique_ptr<Implementation, ImplementationDeleter> m_impl;
};

class ExtendedInterface : public Interface
{
public:
    using Interface::Interface;

    virtual void print() const override;
    virtual void reset();
};
