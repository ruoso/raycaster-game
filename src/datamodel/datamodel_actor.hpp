#ifndef INCLUDED_DATAMODEL_ACTOR_HPP
#define INCLUDED_DATAMODEL_ACTOR_HPP

#include <memory>

#include "datamodel_commontypes.hpp"

namespace raycaster {
  namespace datamodel {

    struct ActorData {
      int id;
      std::string type;
      commontypes::position2d pos = commontypes::position2d(0.0, 0.0);
      commontypes::speed2d speed = commontypes::speed2d(0.0, 0.0);
      units::angle angle = 0;
      double health = 0;
      double radius = 0;
    };

    struct Actor {
      const std::shared_ptr<const ActorData> data;
      Actor(const ActorData& data_in) :data(std::make_shared<ActorData>(data_in)) {}
      Actor(const Actor& a) :data(a.data) {}
      bool operator < (const Actor& a) const {
        return data->id < a.data->id;
      }
      bool operator == (const Actor& a) const {
        return data->id == a.data->id;
      }
    };

  }
}

#endif
