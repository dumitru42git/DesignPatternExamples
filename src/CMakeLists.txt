cmake_minimum_required (VERSION 3.23)

include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.12.0
)
FetchContent_MakeAvailable(json)

add_subdirectory("1_singleton")
add_subdirectory("2_factory_method")
add_subdirectory("3_abstract_factory_pattern")
add_subdirectory("4_builder_pattern")
