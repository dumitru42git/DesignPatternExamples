#include "implementation_factory.h"
//
#include "../private/implementation.h"

void ImplementationDeleter::operator()(Implementation* ptr)
{
    if (ptr)
        delete ptr;
}

std::unique_ptr<Implementation, ImplementationDeleter> ImplementationAFactory::create(const int data) const
{
    return std::unique_ptr<Implementation, ImplementationDeleter>(new ImplementationA(data));
}

std::unique_ptr<Implementation, ImplementationDeleter> ImplementationBFactory::create(const int data) const
{
    return std::unique_ptr<Implementation, ImplementationDeleter>(new ImplementationB(data));
}
