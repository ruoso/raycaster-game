#ifndef INCLUDED_GAMEMATH_RAYCAST_HPP
#define INCLUDED_GAMEMATH_RAYCAST_HPP

#include <tuple>
#include <variant>

#include <datamodel_gamestate.hpp>
#include <datamodel_actor.hpp>
#include <datamodel_tile.hpp>
#include <datamodel_units.hpp>
#include <datamodel_commontypes.hpp>

namespace raycaster {
  namespace gamemath {
    typedef std::variant<datamodel::Actor, datamodel::Tile, nullptr_t>
    raycast_hit_type;
    typedef std::tuple< datamodel::commontypes::position2d, raycast_hit_type>
    raycast_return;
    
    // given start and end positions, return the position where it
    // would be stopped by a wall or an enemy, or nothing
    raycast_return raycast(datamodel::commontypes::position2d start,
                           datamodel::commontypes::position2d end,
                           datamodel::GameState);
  }
}


#endif
