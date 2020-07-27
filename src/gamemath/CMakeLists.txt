add_library(
  gamemath

  OBJECT

  gamemath_camera2d.hpp
  gamemath_camera2d.cpp
  gamemath_camera3d.hpp
  gamemath_camera3d.cpp
  gamemath_distances.hpp
  gamemath_distances.cpp
  gamemath_raycast.hpp
  gamemath_raycast.cpp
  
  )

target_include_directories( gamemath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( gamemath PRIVATE datamodel )
