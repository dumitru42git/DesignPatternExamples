cmake_minimum_required (VERSION 3.23)

add_executable (DoubleCheckedLocking "src/main.cpp" "src/atomic_with_mutex.h" "src/atomic_only.h")
set_property(TARGET DoubleCheckedLocking PROPERTY CXX_STANDARD 23)
