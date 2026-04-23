cmake_minimum_required (VERSION 3.23)

add_executable (Command "src/main.cpp" "src/command.h" "src/invoker.h" "src/data.h")
set_property(TARGET Command PROPERTY CXX_STANDARD 23)
