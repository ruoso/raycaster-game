add_library(
  datamodel OBJECT

  datamodel_actor.cpp
  datamodel_actor.hpp
  datamodel_commontypes.cpp
  datamodel_commontypes.hpp
  datamodel_numeric_value.cpp
  datamodel_numeric_value.hpp
  datamodel_tile.hpp
  datamodel_tile.cpp
  datamodel_tilemap.hpp
  datamodel_tilemap.cpp
  datamodel_tiletype.hpp
  datamodel_tiletype.cpp
  datamodel_tiletypestate.hpp
  datamodel_tiletypestate.cpp
  datamodel_units.cpp
  datamodel_units.hpp

  )


target_include_directories( datamodel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
