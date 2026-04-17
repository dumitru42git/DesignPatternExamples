#include "public/implementation_factory.h"
#include "public/interface.h"

#include <memory>
#include <print>

std::unique_ptr<ImplementationFactory> getImplementationFactory();

int main()
{
    std::println("---Bridge Pattern w/ Pimpl---");

    using ImplementationUptr = std::unique_ptr<Implementation, ImplementationDeleter>;

    {
        ImplementationUptr impl1 = getImplementationFactory()->create(1);
        ImplementationUptr impl2 = getImplementationFactory()->create(42);
        Interface          interface1(std::move(impl1));
        Interface          interface2(std::move(impl2));
        interface1.print();
        interface2.print();
    }
    {
        ImplementationUptr impl1 = getImplementationFactory()->create(1);
        ImplementationUptr impl2 = getImplementationFactory()->create(42);
        ExtendedInterface  interface1(std::move(impl1));
        ExtendedInterface  interface2(std::move(impl2));

        interface1.reset();
        interface1.print();

        interface2.reset();
        interface2.print();
    }

    return 0;
}

std::unique_ptr<ImplementationFactory> getImplementationFactory()
{
    std::unique_ptr<ImplementationFactory> factory;
    static int                             index = 0;

    if (index % 2 == 0)
        factory = std::make_unique<ImplementationAFactory>();
    else
        factory = std::make_unique<ImplementationBFactory>();

    index++;
    return factory;
}
