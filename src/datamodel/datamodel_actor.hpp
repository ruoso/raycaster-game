#ifndef INCLUDED_DATAMODEL_ACTOR_HPP
#define INCLUDED_DATAMODEL_ACTOR_HPP

#include <memory>

#include "datamodel_commontypes.hpp"

namespace raycaster {
  namespace datamodel {

    struct ActorData {
      commontypes::position pos = commontypes::position(0.0, 0.0);
      units::speed speed_x = units::speed(0.0);
      units::speed speed_y = units::speed(0.0);
      units::acceleration acc_x = units::acceleration(0.0);
      units::acceleration acc_y = units::acceleration(0.0);
      double angle = 0;
      double health = 0;
    };

    struct Actor {
      const std::shared_ptr<const ActorData> data;
      Actor(const ActorData& data_in) :data(std::make_shared<ActorData>(data_in)) {}
      Actor(const Actor& a) :data(a.data) {}
    };

  }
}

#endif
