add_executable(
  toy5-3d-raycast

  main.cpp
  )

target_include_directories(toy5-3d-raycast PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(toy5-3d-raycast PRIVATE ${SDL2_LIBRARIES} gameloader datamodel gamemath )
