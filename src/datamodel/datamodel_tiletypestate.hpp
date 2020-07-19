#ifndef INCLUDED_DATAMODEL_TILETYPESTATE_HPP
#define INCLUDED_DATAMODEL_TILETYPESTATE_HPP

#include <string>
#include <stdint.h>

namespace raycaster {
  namespace datamodel {
    struct TileTypeState {
      std::string name;
      uint8_t wall_collision_map;
    };
  }
}

#endif
