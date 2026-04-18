cmake_minimum_required (VERSION 3.23)

add_executable (Composite "src/main.cpp" "src/class.h" "src/composite.h" "src/simple.h")
set_property(TARGET Composite PROPERTY CXX_STANDARD 23)
