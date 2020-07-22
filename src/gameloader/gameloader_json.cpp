#include "gameloader_json.hpp"

#include <nlohmann/json.hpp>

namespace raycaster {
  namespace gameloader {
    namespace JSON {
      datamodel::GameLevel load_game_level_from_json(std::string_view content) {
        auto j = nlohmann::json::parse(content);
        
      }
    }
  }
}
