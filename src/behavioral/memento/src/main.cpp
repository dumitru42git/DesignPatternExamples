#include "public/implementation.h"
#include "public/interface.h"

#include <print>

int main()
{
    std::println("---Memento Pattern w/ Pimpl---");

    auto objectA  = Interface::create<ImplementationA>(5);
    auto mementoA = objectA->save();
    objectA->print();

    auto objectB  = Interface::create<ImplementationB>(42);
    auto mementoB = objectB->save();
    objectB->print();

    std::println();
    std::println("ObjectA <- MementoB");
    objectA->load(std::move(mementoB));
    
    std::println("ObjectB <- MementoA");
    objectB->load(std::move(mementoA));
    std::println();

    objectA->print();
    objectB->print();

    return 0;
}
