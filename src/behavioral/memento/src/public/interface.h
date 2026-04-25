#pragma once

#include "implementation.h"

#include <memory>

class Interface
{
public:
    using ImplPtr = std::unique_ptr<Implementation, ImplementationDeleter>;
    using Memento = ImplPtr;

public:
    template<typename Implementation>
    static std::unique_ptr<Interface> create(int data);

public:
    virtual void    print() const;
    virtual Memento save() const;
    virtual void    load(Memento memento);

    virtual ~Interface();

private:
    std::unique_ptr<Implementation, ImplementationDeleter> m_impl;
};
