cmake_minimum_required (VERSION 3.23)

add_executable (Mediator "src/main.cpp" "src/mediator.h" "src/class.h")
set_property(TARGET Mediator PROPERTY CXX_STANDARD 23)
