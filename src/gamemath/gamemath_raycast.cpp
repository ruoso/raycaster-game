#include "gamemath_raycast.hpp"

namespace raycaster {
  namespace gamemath {

    typedef std::variant<datamodel::Actor, datamodel::Tile, nullptr_t>
    raycast_hit_type;
    typedef std::tuple< datamodel::commontypes::position2d, raycast_hit_type>
    raycast_return;
    
    raycast_return raycast(datamodel::commontypes::position2d start,
                           datamodel::commontypes::position2d end,
                           datamodel::GameState) {

      return raycast_return(datamodel::commontypes::position2d(0.0, 0.0), raycast_hit_type(nullptr));
    }

  }
}
