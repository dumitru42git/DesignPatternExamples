#include "class.h"
#include "mediator.h"

#include <array>
#include <print>
#include <ranges>

template<std::size_t Count>
consteval Class::CastType CastTypeFromCount()
{
    switch (Count)
    {
        case 0:
            return Class::CastType::BROADCAST;
        case 1:
            return Class::CastType::UNICAST;
        default:
            return Class::CastType::MULTICAST;
    }
}

int main()
{
    std::println("---Mediator Pattern---");
    std::println();

    Mediator           mediator;
    std::vector<Class> objects{Class::CastType::UNICAST,
                               Class::CastType::UNICAST | Class::CastType::UNICAST,
                               Class::CastType::BROADCAST | Class::CastType::MULTICAST,
                               Class::CastType::ALL,
                               Class::CastType::MULTICAST};

    for (auto& object : objects)
        mediator.addListener(object);

    auto SendMessage = [&](Class& sender, auto... ids) {
        std::println("id = {}, cast   = {:9}{}",
                     sender.id(),
                     CastTypeFromCount<sizeof...(ids)>(),
                     (sizeof...(ids) > 0) //
                         ? std::format(", targets   = {}", std::array<Class::ID, sizeof...(ids)>{ids...})
                         : "" //
        );
        mediator.sendMessage(sender, ids...);

        for (auto& object : objects)
        {
            std::println("id = {}, allows = {:9}, processed = {}",
                         object.id(),
                         object.allowedReceiveCastType(),
                         object.processed());
        }
        std::println();
    };

    SendMessage(objects[0]);
    SendMessage(objects[0], 1);
    SendMessage(objects[1], 1);
    SendMessage(objects[2], 1, 3, 5);

    Class object6(Class::CastType::ALL);
    SendMessage(object6);

    return 0;
}
