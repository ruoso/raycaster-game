#ifndef INCLUDED_DATAMODEL_TILETYPESTATE_HPP
#define INCLUDED_DATAMODEL_TILETYPESTATE_HPP

#include <memory>
#include <string>
#include <stdint.h>

namespace raycaster {
  namespace datamodel {

    const uint8_t WALL_COLLIDE_NORTH = 8;
    const uint8_t WALL_COLLIDE_SOUTH = 4;
    const uint8_t WALL_COLLIDE_EAST  = 2;
    const uint8_t WALL_COLLIDE_WEST  = 1;
    
    struct TileTypeStateData {
      std::string name;
      uint8_t wall_collision_map;
    };
    
    struct TileTypeState {
      const std::shared_ptr<const TileTypeStateData> data;
      TileTypeState( const TileTypeStateData& data_in ) :data(std::make_shared<TileTypeStateData>(data_in)) {}
      TileTypeState( const TileTypeState& t ) :data(t.data) {}
    };
  }
}

#endif
