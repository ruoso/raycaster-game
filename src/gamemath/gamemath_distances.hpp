#ifndef INCLUDED_GAMEMATH_DISTANCES_HPP
#define INCLUDED_GAMEMATH_DISTANCES_HPP

#include <datamodel_units.hpp>
#include <datamodel_commontypes.hpp>

namespace raycaster {
  namespace gamemath {

    // returns the distance between two points
    datamodel::units::distance
    distance_between_positions(const datamodel::commontypes::position2d& a,
                               const datamodel::commontypes::position2d& b);
   
    // returns the point in a segment that is the closest to the given point
    datamodel::commontypes::position2d
    closest_from_point_to_line_segment(const datamodel::commontypes::position2d& pos,
                                       const datamodel::commontypes::position2d& line_a,
                                       const datamodel::commontypes::position2d& line_b);

    // returns the distance between position and a line segment, defined by two points
    datamodel::units::distance
    distance_between_position_and_line_segment(const datamodel::commontypes::position2d& pos,
                                               const datamodel::commontypes::position2d& line_a,
                                               const datamodel::commontypes::position2d& line_b);
  }
}

#endif
