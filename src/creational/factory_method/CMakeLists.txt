cmake_minimum_required (VERSION 3.23)

add_executable (FactoryMethod "src/main.cpp" "src/class.cpp" "src/class.h" "src/factory.cpp" "src/factory.h")
set_property(TARGET FactoryMethod PROPERTY CXX_STANDARD 23)
target_link_libraries(FactoryMethod PUBLIC nlohmann_json)
