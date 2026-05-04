cmake_minimum_required (VERSION 3.23)

add_executable (ThreadPool "src/main.cpp" "src/thread.h")
set_property(TARGET ThreadPool PROPERTY CXX_STANDARD 23)
