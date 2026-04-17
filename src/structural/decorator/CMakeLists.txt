cmake_minimum_required (VERSION 3.23)

add_executable (Decorator "src/main.cpp" "src/class.h" "src/decorator.h")
set_property(TARGET Decorator PROPERTY CXX_STANDARD 23)
