add_library(
  gamemath

  OBJECT

  gamemath_distances.hpp
  gamemath_distances.cpp
  gamemath_raycast.hpp
  gamemath_raycast.cpp
  
  )

target_link_libraries( gamemath PRIVATE datamodel )
