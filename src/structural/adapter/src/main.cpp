#include "adaptee.h"
#include "adapter.h"
#include "object.h"

#include <print>
#include <vector>

int main()
{
    std::println("---Adapter Pattern---");

    Adaptee adaptee;

    ConcreteObject    concrete;
    ObjectAdapterView objectAdapter(adaptee);
    ClassAdapter      classAdapter;

    std::vector<std::reference_wrapper<IObject>> objects{concrete, objectAdapter, classAdapter};

    int i = 0;
    for (auto object : objects)
    {
        object.get().setData(42 + (i++));
        object.get().print();
    }

    return 0;
}
