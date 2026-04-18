#include "class.h"
#include "composite.h"
#include "simple.h"

#include <concepts>
#include <memory>
#include <print>
#include <vector>

std::unique_ptr<Class> makeSimple(auto&&... args)
{
    return std::make_unique<SimpleClass>(std::forward<decltype(args)>(args)...);
}

std::unique_ptr<Class> makeComposite(std::same_as<std::unique_ptr<Class>> auto... objects)
{
    std::vector<std::unique_ptr<Class>> objectVector;
    (objectVector.push_back(std::move(objects)), ...);

    return std::make_unique<CompositeClass>(std::move(objectVector));
}

int main()
{
    std::println("---Composite Pattern---");

    std::vector<std::unique_ptr<Class>> objects;
    objects.push_back(makeSimple(1));
    objects.push_back(makeComposite(makeSimple(2), makeSimple(3)));
    objects.push_back(makeComposite(makeSimple(4), makeComposite(makeSimple(5), makeSimple(6))));

    for (auto& object : objects)
        object->print();
}
