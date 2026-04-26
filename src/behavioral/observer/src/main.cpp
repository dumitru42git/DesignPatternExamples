#include "observer.h"
#include "observers/observer_append.h"
#include "observers/observer_sum.h"
//
#include "subject.h"
#include "subjects/subject_print.h"
#include "subjects/subject_string.h"
#include "subjects/subject_value.h"

#include <array>
#include <iostream>
#include <memory>
#include <print>

void printlns(int count = 0);

int main()
{
    std::println("---Observer Pattern---");
    std::println();

    std::unique_ptr<Subject> subjectString = std::make_unique<SubjectString>("z");
    std::unique_ptr<Subject> subjectValue  = std::make_unique<SubjectValue>(5);
    std::unique_ptr<Subject> subjectPrint  = std::make_unique<SubjectPrint>(std::cout);

    std::unique_ptr<Observer> observerSum    = std::make_unique<ObserverSum>();
    std::unique_ptr<Observer> observerAppend = std::make_unique<ObserverAppend>();

    for (auto* const observer : std::array{observerSum.get(), observerAppend.get()})
    {
        observer->attachTo(*subjectString);
        observer->attachTo(*subjectValue);
        observer->attachTo(*subjectPrint);
    }

    printlns(1);
    subjectString->attach(*observerSum);
    observerSum->attachTo(*subjectString);
    subjectString->detach(*observerSum);
    subjectString->detach(*observerSum);
    subjectString->attach(*observerSum);

    printlns(1);
    {
        subjectPrint->notify();

        subjectValue->notify();
        subjectValue->notify();
        subjectPrint->notify();

        subjectString->notify();
        subjectPrint->notify();
    }
    printlns();
    {
        subjectString->notify();
        subjectString->notify();
        subjectPrint->notify();
    }
    printlns();
    {
        subjectString->detach(*observerAppend), std::println();
        subjectString->notify();
        subjectString->notify();
        subjectString->attach(*observerAppend), std::println();
        subjectString->notify();
        subjectPrint->notify();
    }

    printlns();
    subjectValue = {};
    observerSum  = {};
    std::println();
    subjectPrint->notify();


    return 0;
}

void printlns(int count)
{
    while (count-- > 0)
        std::println();
    std::println("-----------------------------------------------");
    std::println();
}
