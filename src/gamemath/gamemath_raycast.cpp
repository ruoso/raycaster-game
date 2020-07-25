#include "gamemath_raycast.hpp"

namespace raycaster {
  namespace gamemath {

    typedef std::variant<datamodel::Actor, datamodel::Tile, nullptr_t>
    raycast_hit_type;
    typedef std::tuple< datamodel::commontypes::position2d, raycast_hit_type>
    raycast_return;
    
    raycast_return raycast(const datamodel::commontypes::position2d& start,
                           const datamodel::commontypes::position2d& end,
                           const datamodel::GameState& state) {

      int start_tile_x = int(start.x.value);
      int start_tile_y = int(start.y.value);
      int end_tile_x = int(end.x.value);
      int end_tile_y = int(end.y.value);
      int max_x = state.x_size;
      int max_y = state.y_size;

      return raycast_return(datamodel::commontypes::position2d(0.0, 0.0), raycast_hit_type(nullptr));
    }

  }
}
