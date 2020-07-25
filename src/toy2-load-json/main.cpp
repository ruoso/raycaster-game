#include <iostream>

#include <string>
#include <fstream>
#include <streambuf>

#include <gameloader_json.hpp>


using namespace raycaster;

int main(int argc, const char** argv) {
  if (argc < 2) {
    return 1;
  }

  std::ifstream t(argv[1]);
  std::string str((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());

  datamodel::GameLevel gl = gameloader::JSON::load_game_level_from_json(str);
  return 0;
}
