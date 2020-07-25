#include "gameloader_json.hpp"

#include <datamodel_commontypes.hpp>
#include <nlohmann/json.hpp>

namespace raycaster {
  namespace gameloader {
    namespace JSON {

      static datamodel::Actor parse_actor(nlohmann::json& j) {
        if (!j.is_object()) {
          throw InvalidJsonException("Actor must be an object");
        }

        auto j_type_it = j.find("type");
        if (j_type_it == j.end() || !j_type_it->is_string()) {
          throw InvalidJsonException("No type field in actor");
        }
        std::string type = j_type_it->get<std::string>();

        auto j_pos_it = j.find("pos");
        if (j_pos_it == j.end() || !j_pos_it->is_array() || j_pos_it->size() != 2) {
          throw InvalidJsonException("no valid value for actor pos");
        }
        if (!j_pos_it->at(0).is_number_float() || !j_pos_it->at(1).is_number_float()) {
          throw InvalidJsonException("not floats in actor pos");
        }
        double pos_x = j_pos_it->at(0).get<double>();
        double pos_y = j_pos_it->at(1).get<double>();

        auto j_vel_it = j.find("vel");
        if (j_vel_it == j.end() || !j_vel_it->is_array() || j_vel_it->size() != 2) {
          throw InvalidJsonException("not a valid value for actor vel");
        }
        if (!j_vel_it->at(0).is_number_float() || !j_vel_it->at(1).is_number_float()) {
          throw InvalidJsonException("not floats in actor vel");
        }
        double vel_x = j_vel_it->at(0).get<double>();
        double vel_y = j_vel_it->at(1).get<double>();
        
        auto j_angle_it = j.find("angle");
        if (j_angle_it == j.end() || !j_angle_it->is_number_float()) {
          throw InvalidJsonException("not a float in actor angle");
        }
        double angle = j_angle_it->get<double>();

        auto j_health_it = j.find("health");
        if (j_health_it == j.end() || !j_health_it->is_number_float()) {
          throw InvalidJsonException("not a float in actor health");
        }
        double health = j_health_it->get<double>();

        auto j_radius_it = j.find("radius");
        if (j_radius_it == j.end() || !j_radius_it->is_number_float()) {
          throw InvalidJsonException("not a float in actor radius");
        }
        double radius = j_radius_it->get<double>();

        return datamodel::Actor({ type,
                                  datamodel::commontypes::position2d(pos_x, pos_y),
                                  datamodel::commontypes::speed2d(vel_x, vel_y),
                                  angle,
                                  health,
                                  radius });
      }
      
      datamodel::GameLevel load_game_level_from_json(std::string_view content) {
        auto j = nlohmann::json::parse(content);

        // load the level metadata, such as tile types, tile type
        // states with their wall collision map
        
        auto j_tileTypes_it = j.find("tileTypes");
        if (j_tileTypes_it == j.end() || !j_tileTypes_it->is_object()) {
          throw InvalidJsonException("no tileTypes key in main json");
        }

        std::map<std::string, datamodel::TileType> tileTypes;
        for (auto j_tt_it = j_tileTypes_it->begin(); j_tt_it != j_tileTypes_it->end(); ++j_tt_it) {
          datamodel::TileTypeData r;
          r.name = j_tt_it.key();
          auto j_tileTypeStates = j_tt_it.value();
          if (!j_tileTypeStates.is_object()) {
            throw InvalidJsonException("invalid states for tile type");
          }
          for (auto j_tts_it = j_tileTypeStates.begin(); j_tts_it != j_tileTypeStates.end(); ++j_tts_it) {
            datamodel::TileTypeStateData stateData;
            stateData.name = j_tts_it.key();
            if (!j_tts_it.value().is_number_unsigned()) {
              throw InvalidJsonException("value of tile type state must be an unsigned integer");
            }                
            stateData.wall_collision_map = j_tts_it.value().get<unsigned int>() & 0xFF;
            r.valid_states.insert(std::pair<std::string, datamodel::TileTypeState>(stateData.name, datamodel::TileTypeState(stateData)));
          }
          tileTypes.insert(std::pair<std::string, datamodel::TileType>(r.name, datamodel::TileType(r)));
        }

        // load the metadata, which references the tile types and
        // states and defines the initial payload for each tile.
        
        unsigned int x_size, y_size;
        std::vector<datamodel::Tile> tiles;
        
        auto j_tileSet_it = j.find("tileSet");
        if (j_tileSet_it == j.end() || !j_tileSet_it->is_object()) {
          throw InvalidJsonException("failed to find tileSet key");
        }

        auto j_x_size = j_tileSet_it->find("x_size");
        if (j_x_size == j_tileSet_it->end() || !j_x_size->is_number_unsigned()) {
          throw InvalidJsonException("tileSet without a valid x_size");
        }
        x_size = j_x_size->get<unsigned int>();
          
        auto j_y_size = j_tileSet_it->find("y_size");
        if (j_y_size == j_tileSet_it->end() || !j_y_size->is_number_unsigned()) {
          throw InvalidJsonException("tileSet without a valid y_size");
        }
        y_size = j_y_size->get<unsigned int>();
          
        auto j_map_it = j_tileSet_it->find("map");
        if (j_map_it == j_tileSet_it->end() || !j_map_it->is_array()) {
          throw InvalidJsonException("tileset without a valid map");
        }

        for (auto j_tiles_it = j_map_it->begin(); j_tiles_it != j_map_it->end(); ++j_tiles_it) {
          if (!j_tiles_it->is_array()) {
            throw InvalidJsonException("Invalid contents for tileSet map");
          }

          auto j_tile_it = j_tiles_it->begin();

          if (j_tile_it == j_tiles_it->end() || !j_tile_it->is_string()) {
            throw InvalidJsonException("Empty array in tileSet map tile");
          }
          std::string tile_type_name = j_tile_it->get<std::string>();
          j_tile_it++;

          if (j_tile_it == j_tiles_it->end() || !j_tile_it->is_string()) {
            throw InvalidJsonException("Missing 2 items in tileSet map tile");
          }
          std::string tile_state_name = j_tile_it->get<std::string>();
          j_tile_it++;

          if (j_tile_it == j_tiles_it->end() || !j_tile_it->is_number()) {
            throw InvalidJsonException("Missing 1 item in tileSet map tile");
          }
          int payload = j_tile_it->get<int>();
          j_tile_it++;

          if (j_tile_it != j_tiles_it->end()) {
            throw InvalidJsonException("Too many items in tileSet map tile");
          }
          
          auto tileTypeIt = tileTypes.find(tile_type_name);
          if (tileTypeIt == tileTypes.end()) {
            throw InvalidJsonException("Tile type not found in tileTypes map");
          }

          const datamodel::TileType& tileType = tileTypeIt->second;

          auto tileStateIt = tileType.data->valid_states.find(tile_state_name);
          if (tileStateIt == tileType.data->valid_states.end()) {
            throw InvalidJsonException("Tile type state not found in valid states");
          }
          
          const datamodel::TileTypeState& tileTypeState = tileStateIt->second;
          
          datamodel::TileData tileData =
            {
             &tileType,
             &tileTypeState,
             payload
            };
          tiles.push_back(datamodel::Tile(tileData));
        }
        if (tiles.size() != x_size*y_size) {
          throw InvalidJsonException("map has wrong size");
        }

        // now load the player, as an actor
        auto j_player_it = j.find("player");
        if (j_player_it == j.end()) {
          throw InvalidJsonException("Missing player as actor");
        }
        datamodel::Actor player = parse_actor(*j_player_it);

        // then load the enemies, as a vector of actors
        std::vector<datamodel::Actor> enemies;
        auto j_enemies_it = j.find("enemies");
        if (j_enemies_it == j.end() || !j_enemies_it->is_array()) {
          throw InvalidJsonException("Invalid enemies array");
        }
        for (auto j_enemy_it = j_enemies_it->begin(); j_enemy_it != j_enemies_it->end(); ++j_enemy_it) {
          enemies.push_back(parse_actor(*j_enemy_it));
        }
        
        // finally assemble the initial state
        datamodel::GameStateData initialStateData =
          {
           player,
           enemies,
           x_size,
           y_size,
           tiles
          };
        datamodel::GameState initialState(initialStateData);

        // and finally the level data itself
        datamodel::GameLevelData gameLevelData =
          {
           initialState,
           tileTypes
          };
        // return the game level
        return datamodel::GameLevel(gameLevelData);
      }
    }
  }
}
