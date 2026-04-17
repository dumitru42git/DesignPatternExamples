#include "class.h"

#include <memory>
#include <print>
#include <vector>

using ObjectVector = std::vector<std::unique_ptr<Class>>;

ObjectVector create_objects()
{
    ObjectVector objects;
    objects.push_back(std::make_unique<ClassA>(1, 2));
    objects.push_back(std::make_unique<ClassB>(0.4));
    return objects;
}

ObjectVector duplicate_objects(const ObjectVector& objectsIn)
{
    ObjectVector objectsOut;
    for (const auto& objectIn : objectsIn)
        objectsOut.push_back(objectIn->clone());
    return objectsOut;
}

void reset_objects(ObjectVector& objects)
{
    for (const auto& object : objects)
        object->reset();
}

void print_objects(const ObjectVector& objects)
{
    for (const auto& object : objects)
        object->print();
}

int main()
{
    std::println("---Prototype Pattern---");

    auto objects     = create_objects();
    auto dup_objects = duplicate_objects(objects);

    std::println("Original:");
    print_objects(objects);

    reset_objects(objects);

    std::println("Original after reset:");
    print_objects(objects);

    std::println("Duplicate:");
    print_objects(dup_objects);

    return 0;
}
