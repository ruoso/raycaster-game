#ifndef INCLUDED_DATAMODEL_TILE_HPP
#define INCLUDED_DATAMODEL_TILE_HPP

#include "datamodel_tiletype.hpp"
#include "datamodel_tiletypestate.hpp"

namespace raycaster {
  namespace datamodel {
    struct Tile {
      TileType type;
      TileTypeState& current_state;
      int current_state_payload;
    };
  }
}

#endif
