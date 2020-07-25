#include "gamemath_distances.hpp"

#include <cmath>

namespace raycaster {
  namespace gamemath {

    // returns the distance between two points
    datamodel::units::distance
    distance_between_positions(const datamodel::commontypes::position2d& a,
                               const datamodel::commontypes::position2d& b) {
      double x_off = std::abs(a.x.value - b.x.value);
      double y_off = std::abs(a.y.value - b.y.value);
      return datamodel::units::distance(std::sqrt(x_off*x_off + y_off*y_off));
    }

    datamodel::commontypes::position2d
    closest_from_point_to_line_segment(const datamodel::commontypes::position2d& pos,
                                       const datamodel::commontypes::position2d& line_a,
                                       const datamodel::commontypes::position2d& line_b) {

      double a = pos.x.value - line_a.x.value;
      double b = pos.y.value - line_a.y.value;
      double c = line_b.x.value - line_a.x.value;
      double d = line_b.y.value - line_a.y.value;

      double dot_product = a * c + b * d;
      double len_squared = c * c + d * d;

      double relation = -1;
      if (len_squared != 0)
        relation = dot_product / len_squared;

      double closest_x, closest_y;
      if (relation < 0) {
        // closest point is line_a
        closest_x = line_a.x.value;
        closest_y = line_a.y.value;
      } else if (relation > 1) {
        // closest point is line_b
        closest_x = line_b.x.value;
        closest_y = line_b.y.value;
      } else {
        // closest point is projection on line
        closest_x = line_a.x.value + relation * c;
        closest_y = line_a.y.value + relation * d;
      }

      return datamodel::commontypes::position2d(closest_x, closest_y);
    }

    // returns the distance between position and a line, defined by two points
    datamodel::units::distance
    distance_between_position_and_line_segment(const datamodel::commontypes::position2d& pos,
                                               const datamodel::commontypes::position2d& line_a,
                                               const datamodel::commontypes::position2d& line_b) {
      return distance_between_positions(pos, closest_from_point_to_line_segment(pos, line_a, line_b));
    }
    
  }
}

