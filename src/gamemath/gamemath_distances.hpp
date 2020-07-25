#ifndef INCLUDED_GAMEMATH_DISTANCES_HPP
#define INCLUDED_GAMEMATH_DISTANCES_HPP

#include <datamodel_units.hpp>
#include <datamodel_commontypes.hpp>

namespace raycaster {
  namespace gamemath {

    // returns the distance between two points
    datamodel::units::distance
    distance_between_positions(datamodel::commontypes::position2d a,
                               datamodel::commontypes::position2d b);

    // returns the distance between position and a line segment, defined by two points
    datamodel::units::distance
    distance_between_position_and_line_segment(datamodel::commontypes::position2d pos,
                                               datamodel::commontypes::position2d line_a,
                                               datamodel::commontypes::position2d line_b);
  }
}

#endif
