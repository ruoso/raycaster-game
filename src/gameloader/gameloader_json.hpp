#ifndef INCLUDED_GAMELOADER_JSON_HPP
#define INCLUDED_GAMELOADER_JSON_HPP

#include <string_view>
#include <datamodel_gamelevel.hpp>

namespace raycaster {
  namespace gameloader {
    namespace JSON {
      datamodel::GameLevel load_game_level_from_json(std::string_view content);
    }
  }
}

#endif
