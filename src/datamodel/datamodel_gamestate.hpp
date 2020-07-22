#ifndef INCLUDED_DATAMODEL_GAMESTATE_HPP
#define INCLUDED_DATAMODEL_GAMESTATE_HPP

#include <memory>
#include <vector>
#include <map>

#include "datamodel_actor.hpp"
#include "datamodel_tile.hpp"

namespace raycaster {
  namespace datamodel {

    struct GameStateData {
      Actor player;
      std::vector<Actor> enemies;
      int x_size;
      int y_size;
      std::vector<Tile> tileset;
    };
      
    
    struct GameState {
      const std::shared_ptr<const GameStateData> data;

      GameState( const GameStateData& data_in ) :data(std::make_shared<GameStateData>(data_in)) {}

      GameState( const GameState& g ) :data(g.data) {}

      const Tile& tile_at(int x, int y) const {
        return data->tileset[x+data->x_size*y];
      }

    };
  }
}

#endif
