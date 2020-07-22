#ifndef INCLUDED_DATAMODEL_GAMERUN_HPP
#define INCLUDED_DATAMODEL_GAMERUN_HPP

#include "datamodel_gamelevel.hpp"
#include "datamodel_gamestate.hpp"

namespace raycaster {
  namespace datamodel {

    class GameRun {
      GameState* current_state;
    public:
      GameLevel level;
      GameRun(GameLevel l) :level(l) {
        current_state = new GameState(l.data->initial_state);
      }

      ~GameRun() {
        delete current_state;
      }

      void checkpoint_state(const GameStateData& newstate) {
        // TODO: lock!
        GameState* saved = current_state;
        current_state = new GameState(newstate);
        delete saved;
      }

      // get a copy of the state
      GameState get_state() {
        // TODO: lock!
        GameState copy(*current_state);
        return copy;
      }
    };
  }
}



#endif
