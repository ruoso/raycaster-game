add_library(
  gameloader OBJECT

  gameloader_json.hpp
  gameloader_json.cpp
  
  )

target_link_libraries( gameloader PRIVATE nlohmann_json::nlohmann_json )
target_include_directories( gameloader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
