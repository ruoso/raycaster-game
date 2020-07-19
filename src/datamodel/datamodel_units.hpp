#ifndef INCLUDED_DATAMODEL_UNITS_HPP
#define INCLUDED_DATAMODEL_UNITS_HPP

#include "datamodel_numeric_value.hpp"

namespace raycaster {
  namespace datamodel {
    namespace units {
      
      // First level units
      class distance;
      class time;
      class mass;

      // Compound units
      class area;
      class speed;
      class acceleration;
      class force;
      
      class distance: public numeric_value<distance> {
      public:
        speed operator / (const time& v);
        area operator * (const distance& v);
      };

      class area: public numeric_value<area> {
      };
      
      class speed: public numeric_value<speed> {
        speed operator / (const time& v);
      };

      class acceleration: public numeric_value<acceleration> {
      };

      class time: public numeric_value<time> {
      };

      class mass: public numeric_value<mass> {
        force operator*(const acceleration& a);
      };

      class force: public numeric_value<force> {
      };

    }
  }
}

#endif
