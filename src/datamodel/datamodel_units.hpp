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
        using numeric_value<distance>::numeric_value;
        speed operator / (const time& v);
        area operator * (const distance& v);
      };

      class area: public numeric_value<area> {
      public:
        using numeric_value<area>::numeric_value;
      };
      
      class speed: public numeric_value<speed> {
      public:
        speed operator / (const time& v);
        using numeric_value<speed>::numeric_value;
      };

      class acceleration: public numeric_value<acceleration> {
      public:
        using numeric_value<acceleration>::numeric_value;
      };

      class time: public numeric_value<time> {
      public:
        using numeric_value<time>::numeric_value;
      };

      class mass: public numeric_value<mass> {
      public:
        using numeric_value<mass>::numeric_value;
        force operator*(const acceleration& a);
      };

      class force: public numeric_value<force> {
      public:
        using numeric_value<force>::numeric_value;
      };

    }
  }
}

#endif
