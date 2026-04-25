#include "implementation.h"
//
#include "..\private\implementation.h"

void ImplementationDeleter::operator()(Implementation* ptr)
{
    delete ptr;
}
