cmake_minimum_required (VERSION 3.23)

add_executable (Iterator "src/main.cpp" "src/iterable.h")
set_property(TARGET Iterator PROPERTY CXX_STANDARD 23)
