#ifndef INCLUDED_GAMELOADER_JSON_HPP
#define INCLUDED_GAMELOADER_JSON_HPP

#include <string_view>
#include <datamodel_gamestate.hpp>

namespace raycaster {
  namespace gameloader {
    namespace JSON {
      datamodel::GameState load_game_state_from_json(std::string_view content);
    }
  }
}

#endif
