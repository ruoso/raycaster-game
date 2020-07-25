add_executable(
  toy2-load-json

  main.cpp

  )

target_link_libraries( toy2-load-json PRIVATE gameloader datamodel )
