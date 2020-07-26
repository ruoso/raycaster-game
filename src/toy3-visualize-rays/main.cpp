#include <iostream>

#include <cmath>
#include <string>
#include <fstream>
#include <streambuf>

#include <gameloader_json.hpp>
#include <gamemath_raycast.hpp>
#include <datamodel_commontypes.hpp>

using namespace raycaster;

int main(int argc, const char** argv) {
  if (argc < 2) {
    return 1;
  }

  std::ifstream t(argv[1]);
  std::string str((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());

  datamodel::GameLevel gl = gameloader::JSON::load_game_level_from_json(str);
  datamodel::GameState s = gl.data->initial_state;
  datamodel::Actor player = s.data->player;
  datamodel::commontypes::position2d pos = player.data->pos;
  double deg360 = std::acos(-1) * 2;
  double max_x = s.data->x_size + 1;
  double max_y = s.data->y_size + 1;
  std::cout << "player : " << pos.x.value << "," << pos.y.value << std::endl;
  for (double a = 0; a < deg360; a += deg360/360) {
    double other_x = pos.x.value + std::cos(a) * max_x;
    double other_y = pos.y.value + std::sin(a) * max_y;

    std::cout << "ray " << a << " " << other_x << "," << other_y << std::endl;
      
    gamemath::raycast_hits hits =
      gamemath::raycast(pos, datamodel::commontypes::position2d(other_x, other_y),
              s, 10);
    for (auto hit : hits) {
      datamodel::commontypes::position2d pos = std::get<0>(hit);
      gamemath::raycast_hit_type ht = std::get<1>(hit);
      std::cout << "\thit\t\t" << pos.x.value << "\t\t" << pos.y.value << "\t\t" << ht.index() << std::endl;
    }
  }
  
  
  return 0;
}
