#include "template_method.h"

#include <memory>
#include <print>

int main()
{
    std::println("---Template Method Pattern---");
    std::println();

    TemplateMethodSquare square(2);
    TemplateMethodExp    exp(2);

    TemplateMethod* ptr = &square;
    ptr->method();
    ptr->method();

    std::println();
    ptr = &exp;
    ptr->method();
    ptr->method();
}
