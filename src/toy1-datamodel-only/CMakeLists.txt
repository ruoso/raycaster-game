
add_executable(
  toy1-datamodel-only

  main.cpp

  )

target_link_libraries( toy1-datamodel-only PRIVATE datamodel )
