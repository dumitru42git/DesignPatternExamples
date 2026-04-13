cmake_minimum_required (VERSION 3.23)

add_executable (AbstractFactoryPattern "src/main.cpp" "src/classA.cpp" "src/classA.h" "src/classB.cpp" "src/classB.h" "src/factory.cpp" "src/factory.h")
set_property(TARGET AbstractFactoryPattern PROPERTY CXX_STANDARD 23)
target_link_libraries(AbstractFactoryPattern PUBLIC nlohmann_json)
