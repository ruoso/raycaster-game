#include <iostream>

#include <datamodel_actor.hpp>
#include <datamodel_gamerun.hpp>
#include <datamodel_gamestate.hpp>
#include <datamodel_gamelevel.hpp>
#include <datamodel_tiletype.hpp>
#include <datamodel_tiletypestate.hpp>

using namespace raycaster;

datamodel::TileType generate_tile_type(const char* floor_type, int wall_collision) {
  std::string name = floor_type;
  name += "_";
  char suffix[5] = "";
  snprintf(suffix, 5, "%1u%1u%1u%1u", wall_collision & 1, wall_collision & 2, wall_collision & 4, wall_collision & 8);
  name += suffix;

  datamodel::TileTypeStateData stateData;
  stateData.name = "default";
  stateData.wall_collision_map = wall_collision;

  datamodel::TileTypeData r;
  r.name = name;
  r.valid_states.insert(std::pair<std::string, datamodel::TileTypeState>(std::string("default"), datamodel::TileTypeState(stateData)));

  return datamodel::TileType(r);
}

int main(int argc, char** argv) {


  std::map<std::string, datamodel::TileType> tileTypes;
  const std::array<const char*, 4> floor_types =
    {
     "enemy_faster",
     "enemy_slower",
     "goal",
     "pit"
    };
  for (auto floor_type : floor_types) {
    for (int i = 0; i < 16; i++) {
      const datamodel::TileType &t = generate_tile_type(floor_type, i);
      tileTypes.insert(std::pair<std::string, datamodel::TileType>(t.data->name, t));
    }
  }

  int x_size, y_size;
  std::cin >> x_size;
  std::cin >> y_size;
  std::vector<datamodel::Tile> tileset;
  
  int count = x_size * y_size;
  while (count > 0) {
    std::string type, state;
    int payload;
    std::cin >> type;
    std::cin >> state;
    std::cin >> payload;

    const datamodel::TileType &typeref = tileTypes[type];
    const datamodel::TileTypeState &stateref = typeref.data->valid_states.at(state);
    datamodel::TileData tileData;
    tileData.type = &typeref;
    tileData.current_state = &stateref;
    tileData.payload = payload;
    tileset.push_back(datamodel::Tile(tileData));
    count--;
  }

  datamodel::ActorData playerData;
  std::vector<datamodel::Actor> enemies;
  datamodel::GameStateData initialStateData =
    {
     playerData,
     enemies,
     x_size,
     y_size,
     tileset
    };
  datamodel::GameState initialState(initialStateData);

  datamodel::GameLevelData gameLevelData =
    {
     initialState,
     tileTypes
    };

  datamodel::GameLevel gameLevel(gameLevelData);

  datamodel::GameRun gameRun(gameLevel);
  datamodel::GameState stateCopy = gameRun.get_state();

  return 0;
}
