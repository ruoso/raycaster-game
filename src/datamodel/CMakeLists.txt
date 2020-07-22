add_library(
  datamodel OBJECT

  datamodel_actor.cpp
  datamodel_actor.hpp
  datamodel_commontypes.cpp
  datamodel_commontypes.hpp
  datamodel_gamelevel.cpp
  datamodel_gamelevel.hpp
  datamodel_gamerun.cpp
  datamodel_gamerun.hpp
  datamodel_gamestate.cpp
  datamodel_gamestate.hpp
  datamodel_numeric_value.cpp
  datamodel_numeric_value.hpp
  datamodel_tile.cpp
  datamodel_tile.hpp
  datamodel_tiletype.cpp
  datamodel_tiletype.hpp
  datamodel_tiletypestate.cpp
  datamodel_tiletypestate.hpp
  datamodel_units.cpp
  datamodel_units.hpp

  )


target_include_directories( datamodel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
