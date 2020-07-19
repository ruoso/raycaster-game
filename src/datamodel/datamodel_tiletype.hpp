#ifndef INCLUDED_DATAMODEL_TILETYPE_HPP
#define INCLUDED_DATAMODEL_TILETYPE_HPP

#include <vector>
#include "datamodel_tiletypestate.hpp"

namespace raycaster {
  namespace datamodel {
    struct TileType {
      std::vector<TileTypeState> valid_states;
    };
  }
}

#endif
