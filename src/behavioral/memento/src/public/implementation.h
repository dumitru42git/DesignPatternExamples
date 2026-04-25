#pragma once

class Implementation;
class ImplementationA;
class ImplementationB;

class ImplementationDeleter
{
public:
    void operator()(Implementation* ptr);
};
