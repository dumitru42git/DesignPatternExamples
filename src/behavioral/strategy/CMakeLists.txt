cmake_minimum_required (VERSION 3.23)

add_executable (Strategy "src/main.cpp" "src/class.h" "src/print.h" "src/print_forward.h" "src/print_reverse.h" "src/print_forward.cpp" "src/print_reverse.cpp" "src/type_traits.h" "src/print.cpp")
set_property(TARGET Strategy PROPERTY CXX_STANDARD 23)
