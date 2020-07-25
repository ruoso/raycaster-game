#ifndef INCLUDED_GAMEMATH_RAYCAST_HPP
#define INCLUDED_GAMEMATH_RAYCAST_HPP

#include <vector>
#include <tuple>
#include <variant>

#include <datamodel_gamestate.hpp>
#include <datamodel_actor.hpp>
#include <datamodel_tile.hpp>
#include <datamodel_units.hpp>
#include <datamodel_commontypes.hpp>

namespace raycaster {
  namespace gamemath {
    typedef std::tuple<datamodel::Tile, uint8_t>
    raycast_hit_wall;
    
    typedef std::variant<datamodel::Actor, raycast_hit_wall, nullptr_t>
    raycast_hit_type;

    typedef std::tuple< datamodel::commontypes::position2d,
                        raycast_hit_type>
    raycast_hit;

    typedef std::vector<raycast_hit>
    raycast_hits;
    
    // given start and end positions, return the position where it
    // would be stopped by a wall or an enemy, or nothing
    raycast_hits raycast(const datamodel::commontypes::position2d& start,
                         const datamodel::commontypes::position2d& end,
                         const datamodel::GameState& state,
                         const int& max_wall_hits,
                         const int& max_enemy_hits);
  }
}


#endif
