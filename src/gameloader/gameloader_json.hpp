#ifndef INCLUDED_GAMELOADER_JSON_HPP
#define INCLUDED_GAMELOADER_JSON_HPP

#include <exception>
#include <string_view>
#include <datamodel_gamelevel.hpp>

namespace raycaster {
  namespace gameloader {
    namespace JSON {

      /**
       * Format of the json file:

       {
         "player": {
           "type": "identifier",
           "pos": [ 0, 0 ],
           "vel": [ 0, 0 ],
           "angle": 0,
           "health": 1
         },
         "enemies": [
           {
             "type": "identifier",
             "pos": [ 0, 0 ],
             "vel": [ 0, 0 ],
             "angle": 0,
             "health": 1
           }
         ],
         "tileTypes": {
           "dirt": {
             "default": 0
           },
           "dirt_1000": {
             "default": 8
           }
           "door_1000": {
             "closed": 8,
             "open": 0,
           }
         },
         "tileSet": {
           "x_size": 2,
           "y_size": 2,
           "map": [
             [ "dirt", "default", 0 ],     [ "dirt", "default", 0 ],
             [ "dirt_100", "default", 0 ], [ "door_1000", "closed", 0 ]
           ]
         }
       }

       */
      datamodel::GameLevel load_game_level_from_json(std::string_view content);

      class InvalidJsonException : public std::exception {
      public:
        const char* msg;
        InvalidJsonException(const char* msg_in) :msg(msg_in) {}
        const char* what() const noexcept override {
          return msg;
        }
      };

    }
  }
}

#endif
