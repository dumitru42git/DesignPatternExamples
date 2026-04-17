#include "class.h"
#include "decorator.h"

#include <memory>
#include <print>
#include <vector>

std::unique_ptr<Class> addPre(std::unique_ptr<Class> object)
{
    return std::make_unique<DecoratorAddIdPre>(std::move(object));
}

std::unique_ptr<Class> addPost(std::unique_ptr<Class> object)
{
    return std::make_unique<DecoratorAddIdPost>(std::move(object));
}

std::unique_ptr<Class> invalidId(std::unique_ptr<Class> object)
{
    return std::make_unique<DecoratorInvalidId>(std::move(object));
}

std::vector<std::unique_ptr<Class>> getObjects()
{
    std::vector<std::unique_ptr<Class>> objects;

    auto object1 = std::make_unique<ClassA>(1, 42);
    auto object2 = std::make_unique<ClassA>(2, 42);
    auto object3 = std::make_unique<ClassA>(3, 42);

    objects.push_back(addPost(addPre(addPost(std::move(object1)))));
    objects.push_back(addPre(invalidId(std::move(object2))));
    objects.push_back(invalidId(std::move(object3)));

    return objects;
}

int main()
{
    std::println("---Decorator Pattern---");

    const auto objects = getObjects();

    for (const auto& object : objects)
        std::println("{}", object->printString());

    return 0;
}
