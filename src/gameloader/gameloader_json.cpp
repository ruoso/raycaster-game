#include "gameloader_json.hpp"

#include <nlohmann/json.hpp>

namespace raycaster {
  namespace gameloader {
    namespace JSON {
      datamodel::GameState load_game_state_from_json(std::string_view content) {
        auto j = nlohmann::json::parse(content);
      }
    }
  }
}
