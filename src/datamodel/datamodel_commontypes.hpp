#ifndef INCLUDED_DATAMODEL_COMMONTYPES_HPP
#define INCLUDED_DATAMODEL_COMMONTYPES_HPP

#include "datamodel_units.hpp"

namespace raycaster {
  namespace datamodel {
    namespace commontypes {
      
      class position {
      public:
        units::distance x;
        units::distance y;
        position( const units::distance &_x, const units::distance &_y ) :x(_x), y(_y) {};
        position( const position& v ) :x(v.x), y(v.y) {};
      };

    }
  }
}

#endif
