cmake_minimum_required (VERSION 3.23)

add_executable (Singleton "src/main.cpp" "src/singleton.cpp" "src/singleton.h")
set_property(TARGET Singleton PROPERTY CXX_STANDARD 23)
