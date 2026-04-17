cmake_minimum_required (VERSION 3.23)

add_executable (Adapter "src/main.cpp" "src/adaptee.h" "src/adapter.h" "src/object.h")
set_property(TARGET Adapter PROPERTY CXX_STANDARD 23)
