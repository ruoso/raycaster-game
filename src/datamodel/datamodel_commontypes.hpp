#ifndef INCLUDED_DATAMODEL_COMMONTYPES_HPP
#define INCLUDED_DATAMODEL_COMMONTYPES_HPP

#include "datamodel_units.hpp"

namespace raycaster {
  namespace datamodel {
    namespace commontypes {

      struct position2d {
        units::distance x;
        units::distance y;
        position2d() :x(0.0), y(0.0) {}
        position2d( const units::distance &_x, const units::distance &_y ) :x(_x), y(_y) {};
        position2d( const position2d& v ) :x(v.x), y(v.y) {};
      };

      struct speed2d {
        units::speed x;
        units::speed y;
        speed2d( ) :x(0.0), y(0.0) {}
        speed2d( const units::speed &_x, const units::speed &_y ) :x(_x), y(_y) {};
        speed2d( const speed2d& v ) :x(v.x), y(v.y) {};
      };

      struct acceleration2d {
        units::acceleration x;
        units::acceleration y;
        acceleration2d( ) :x(0.0), y(0.0) {}
        acceleration2d( const units::acceleration &_x, const units::acceleration &_y ) :x(_x), y(_y) {};
        acceleration2d( const acceleration2d& v ) :x(v.x), y(v.y) {};
      };

    }
  }
}

#endif
