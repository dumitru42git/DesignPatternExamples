cmake_minimum_required (VERSION 3.23)

add_executable (Proxy "src/main.cpp" "src/proxy.h" "src/class.h")
set_property(TARGET Proxy PROPERTY CXX_STANDARD 23)
