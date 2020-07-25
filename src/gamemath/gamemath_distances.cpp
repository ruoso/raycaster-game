#include "gamemath_distances.hpp"

namespace raycaster {
  namespace gamemath {

    // returns the distance between two points
    datamodel::units::distance
    distance_between_positions(datamodel::commontypes::position2d a,
                               datamodel::commontypes::position2d b) {
      return datamodel::units::distance(0.0);
    }

    // returns the distance between position and a line, defined by two points
    datamodel::units::distance
    distance_between_position_and_line_segment(datamodel::commontypes::position2d pos,
                                               datamodel::commontypes::position2d line_a,
                                               datamodel::commontypes::position2d line_b) {
      return datamodel::units::distance(0.0);
    }
    
  }
}

