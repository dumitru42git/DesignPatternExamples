#pragma once

#include <memory>

class Implementation;
class ImplementationDeleter
{
public:
    void operator()(Implementation* ptr);
};

class ImplementationFactory
{
public:
    virtual std::unique_ptr<Implementation, ImplementationDeleter> create(int data) const = 0;

    virtual ~ImplementationFactory() = default;
};

class ImplementationAFactory : public ImplementationFactory
{
public:
    std::unique_ptr<Implementation, ImplementationDeleter> create(int data) const override;
};

class ImplementationBFactory : public ImplementationFactory
{
public:
    std::unique_ptr<Implementation, ImplementationDeleter> create(int data) const override;
};
