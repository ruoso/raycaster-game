#ifndef INCLUDED_DATAMODEL_TILEMAP_HPP
#define INCLUDED_DATAMODEL_TILEMAP_HPP

#include <vector>
#include "datamodel_tile.hpp"

namespace raycaster {
  namespace datamodel {
    struct TileMap {
      int max_x;
      int max_y;
      std::vector< std::vector< Tile > > tileset;
    };
  }
}

#endif
