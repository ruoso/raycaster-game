#ifndef INCLUDED_DATAMODEL_NUMERIC_VALUE_HPP
#define INCLUDED_DATAMODEL_NUMERIC_VALUE_HPP

#include <cstdlib>
#include <cmath>
#include <limits>

namespace raycaster {
  namespace datamodel {

    template <class C>
    struct numeric_value {
      double value;
      inline numeric_value(double v) :value(v) {}
      inline numeric_value(const C& v) :value(v.value) {}
      inline void operator=(const C& v) { value = v; }
      
      inline numeric_value operator + (C v) { return numeric_value( value + v.value); }
      inline numeric_value operator - (C v) { return numeric_value( value - v.value); }
      
      inline void operator += (C v) { value += v.value; }
      inline void operator -= (C v) { value -= v.value; }
      
      inline C operator ++ () { return ++value; }
      inline C operator -- () { return --value;}
      inline C operator ++ (int v) { return value++; }
      inline C operator -- (int v) { return value--; }
      
      // avoid rounding errors when comparing
      inline bool operator == (C v) {
        return
          std::fabs(value - v.value) <= std::numeric_limits<double>::epsilon() * std::fabs(value + v.value) * std::numeric_limits<double>::round_error
          || std::fabs(value - v.value) < std::numeric_limits<double>::min();
      }
      inline bool operator != (C v) { return !(this == v); }
      inline bool operator > (C v) { return value > v.value; }
      inline bool operator < (C v) { return value < v.value; }
      inline bool operator >= (C v) { return value >= v.value; }
      inline bool operator <= (C v) { return value <= v.value; }        
    };

  }
}

#endif
