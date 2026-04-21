cmake_minimum_required (VERSION 3.23)

add_executable (Facade "src/main.cpp" "src/classA.h" "src/classB.h" "src/classC.h" "src/facade.h")
set_property(TARGET Facade PROPERTY CXX_STANDARD 23)
