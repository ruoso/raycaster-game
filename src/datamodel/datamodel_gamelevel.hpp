#ifndef INCLUDED_DATAMODEL_GAMELEVEL_HPP
#define INCLUDED_DATAMODEL_GAMELEVEL_HPP

#include <memory>
#include <map>
#include <string>

#include "datamodel_gamestate.hpp"
#include "datamodel_tiletype.hpp"

namespace raycaster {
  namespace datamodel {

    struct GameLevelData {
      GameState initial_state;
      std::map<std::string,TileType> tileTypes;
    };
    
    struct GameLevel {
      const std::shared_ptr<const GameLevelData> data;
      GameLevel(const GameLevelData& data_in) :data(std::make_shared<GameLevelData>(data_in)) {}
      GameLevel(const GameLevel& g) :data(g.data) {}
    };

  }
}


#endif
