add_executable(
  toy3-visualize-rays

  main.cpp

  )

target_link_libraries( toy3-visualize-rays PRIVATE gameloader datamodel gamemath )
