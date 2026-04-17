cmake_minimum_required (VERSION 3.23)

add_executable (PrototypePattern "src/main.cpp" "src/class.cpp" "src/class.h")
set_target_properties(PrototypePattern PROPERTIES CXX_STANDARD 23)
