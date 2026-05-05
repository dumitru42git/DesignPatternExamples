cmake_minimum_required (VERSION 3.23)

add_executable (ActiveObject "src/main.cpp" "src/active_object.h")
set_property(TARGET ActiveObject PROPERTY CXX_STANDARD 23)
