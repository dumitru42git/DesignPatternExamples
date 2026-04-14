cmake_minimum_required (VERSION 3.23)

add_executable (BuilderPattern "src/main.cpp" "src/class.cpp" "src/class.h" "src/builder.cpp" "src/builder.h")
set_target_properties(BuilderPattern PROPERTIES CXX_STANDARD 23)
target_link_libraries(BuilderPattern PUBLIC nlohmann_json)
