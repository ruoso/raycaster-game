cmake_minimum_required( VERSION 3.12 )
project( raycaster VERSION 0.0.1 LANGUAGES CXX )
set( CMAKE_CXX_STANDARD 17 )

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_compile_options( -Wall -Werror )

add_subdirectory(src)
