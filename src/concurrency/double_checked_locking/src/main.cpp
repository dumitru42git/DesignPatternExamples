#include "atomic_only.h"
#include "atomic_with_mutex.h"

#include <print>

int main()
{
    std::println("---Double-Checked Locking Pattern---");

    atomic_with_mutex();
    atomic_only();

    return 0;
}
