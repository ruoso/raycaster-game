#ifndef INCLUDED_DATAMODEL_ACTOR_HPP
#define INCLUDED_DATAMODEL_ACTOR_HPP

#include "datamodel_commontypes.hpp"

namespace raycaster {
  namespace datamodel {
    struct Actor {
      commontypes::position pos;
      units::speed speed_x;
      units::speed speed_y;
      units::acceleration acc_x;
      units::acceleration acc_y;
      double angle;
      double health;
      virtual ~Actor() {};
    };
  }
}

#endif
