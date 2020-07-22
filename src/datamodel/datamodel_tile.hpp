#ifndef INCLUDED_DATAMODEL_TILE_HPP
#define INCLUDED_DATAMODEL_TILE_HPP

#include <memory>

#include "datamodel_tiletype.hpp"
#include "datamodel_tiletypestate.hpp"

namespace raycaster {
  namespace datamodel {

    struct TileData {
      const TileType* type;
      const TileTypeState* current_state;
      int payload;
    };
    
    struct Tile {
      const std::shared_ptr<const TileData> data;
      Tile(const TileData& data_in) :data(std::make_shared<TileData>(data_in)) {}
      Tile(const Tile& t) :data(t.data) {}
    };

  }
}

#endif
