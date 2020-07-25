#ifndef INCLUDED_DATAMODEL_NUMERIC_VALUE_HPP
#define INCLUDED_DATAMODEL_NUMERIC_VALUE_HPP

#include <cstdlib>
#include <cmath>
#include <limits>

namespace raycaster {
  namespace datamodel {

    template <class C>
    class numeric_value {
    public:
      double value;
      numeric_value(double v) :value(v) {}
      numeric_value(const C& v) :value(v.value) {}
      void operator=(const C& v) { value = v; }
      
      numeric_value operator + (C v) const { return numeric_value( value + v.value); }
      numeric_value operator - (C v) const { return numeric_value( value - v.value); }
     
      // avoid rounding errors when comparing
      bool operator == (C v) const {
        return
          std::fabs(value - v.value) <= std::numeric_limits<double>::epsilon() * std::fabs(value + v.value) * std::numeric_limits<double>::round_error()
          || std::fabs(value - v.value) < std::numeric_limits<double>::min();
      }
      bool operator != (C v) const { return !(this == v); }
      bool operator > (C v) const { return value > v.value; }
      bool operator < (C v) const { return value < v.value; }
      bool operator >= (C v) const { return value >= v.value; }
      bool operator <= (C v) const { return value <= v.value; }        
    };

  }
}

#endif
