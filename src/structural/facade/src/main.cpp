#include "facade.h"

int main()
{
    std::println("---Facade Pattern---");

    std::println("Facade::run() -> {}", Facade{}.run());

    return 0;
}
