add_executable(
  toy4-sdl-rays

  main.cpp
  )

target_include_directories(toy4-sdl-rays PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(toy4-sdl-rays PRIVATE ${SDL2_LIBRARIES} gameloader datamodel gamemath )
