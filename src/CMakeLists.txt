cmake_minimum_required (VERSION 3.23)

include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.12.0
)
FetchContent_MakeAvailable(json)

add_subdirectory("creational")
add_subdirectory("structural")
add_subdirectory("behavioral")
add_subdirectory("concurrency")
