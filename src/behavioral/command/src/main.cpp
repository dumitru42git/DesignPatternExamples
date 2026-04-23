#include "command.h"
#include "data.h"
#include "invoker.h"

#include <print>

int main()
{
    std::println("---Command Pattern---");
    std::println();

    Data data{.value = 42};

    Invoker invoker;
    invoker.addCommand(std::make_unique<AddCommand>(data, 8));
    invoker.addCommand(std::make_unique<SetCommand>(data, Data{.value = 1}));
    invoker.addCommand(std::make_unique<AddCommand>(data, -2));

    invoker.execute();
    invoker.execute();

    invoker.undo();
    invoker.undo();

    invoker.redo();
    invoker.execute();
    invoker.redo();

    invoker.undo();
    invoker.undo();
    invoker.undo();

    invoker.execute();

    return 0;
}
