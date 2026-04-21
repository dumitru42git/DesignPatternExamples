cmake_minimum_required (VERSION 3.23)

add_executable (Flyweight "src/main.cpp" "src/font.h" "src/renderer.h" "src/font_manager.h")
set_property(TARGET Flyweight PROPERTY CXX_STANDARD 23)
