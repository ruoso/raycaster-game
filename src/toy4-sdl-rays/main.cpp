#include <iostream>

#include <cmath>
#include <string>
#include <fstream>
#include <streambuf>

#include <SDL.h>

#include <gameloader_json.hpp>
#include <gamemath_raycast.hpp>
#include <datamodel_commontypes.hpp>
#include <gamemath_camera2d.hpp>
#include <datamodel_gamerun.hpp>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

using namespace raycaster;

void draw_player(gamemath::Camera2D camera, SDL_Renderer* renderer, const datamodel::Actor& player) {
  // find a position 0.1 left, based on the angle
  double tri_a_x = player.data->pos.x.value - std::sin(player.data->angle.value)*0.1;
  double tri_a_y = player.data->pos.y.value + std::cos(player.data->angle.value)*0.1;
  // find a position 0.1 right, based on the angle
  double tri_b_x = player.data->pos.x.value + std::sin(player.data->angle.value)*0.1;
  double tri_b_y = player.data->pos.y.value - std::cos(player.data->angle.value)*0.1;
  // find a position 0.1 in front, based on the angle
  double tri_c_x = player.data->pos.x.value + std::cos(player.data->angle.value)*0.1;
  double tri_c_y = player.data->pos.y.value + std::sin(player.data->angle.value)*0.1;

  gamemath::Camera2DPixelPosition tri_a_pos = camera.point_to_pixel( datamodel::commontypes::position2d( tri_a_x, tri_a_y ) );
  gamemath::Camera2DPixelPosition tri_b_pos = camera.point_to_pixel( datamodel::commontypes::position2d( tri_b_x, tri_b_y ) );
  gamemath::Camera2DPixelPosition tri_c_pos = camera.point_to_pixel( datamodel::commontypes::position2d( tri_c_x, tri_c_y ) );

  SDL_SetRenderDrawColor(renderer, 0, 0, 150, 50);
  SDL_RenderDrawLine( renderer,
                      tri_a_pos.x, tri_a_pos.y,
                      tri_b_pos.x, tri_b_pos.y);
  SDL_RenderDrawLine( renderer,
                      tri_a_pos.x, tri_a_pos.y,
                      tri_c_pos.x, tri_c_pos.y);
  SDL_RenderDrawLine( renderer,
                      tri_b_pos.x, tri_b_pos.y,
                      tri_c_pos.x, tri_c_pos.y);
}

void draw_frame(gamemath::Camera2D camera, SDL_Renderer* renderer, datamodel::GameState s) {
  //Fill the surface white
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);
  SDL_RenderClear(renderer);

  const datamodel::Actor& player = s.data->player;
  const datamodel::commontypes::position2d& pos = player.data->pos;
  gamemath::Camera2DPixelPosition player_pixel_pos = camera.point_to_pixel( pos );
  double max_x = s.data->x_size + 1;
  double max_y = s.data->y_size + 1;

  double deg360 = std::acos(-1) * 2;
  for (double a = player.data->angle.value - deg360/6; a < player.data->angle.value + deg360/6; a += 0.01) {
    double other_x = pos.x.value + std::cos(a) * max_x*2;
    double other_y = pos.y.value + std::sin(a) * max_y*2;
    gamemath::raycast_hits hits =
      gamemath::raycast(pos, datamodel::commontypes::position2d(other_x, other_y),
              s, 1);
    for (auto hit : hits) {
      datamodel::commontypes::position2d pos = std::get<0>(hit);
      gamemath::raycast_hit_type ht = std::get<1>(hit);
      if (ht.index() == 0) {
        SDL_SetRenderDrawColor(renderer, 95, 0, 0, 50);
      } else {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 50);
      }
      gamemath::Camera2DPixelPosition hit_pos = camera.point_to_pixel( pos );
      SDL_RenderDrawLine( renderer,
                          player_pixel_pos.x, player_pixel_pos.y,
                          hit_pos.x, hit_pos.y );
      break;
    }
  }
  
  draw_player(camera, renderer, player);
  SDL_RenderPresent(renderer);
}

int main(int argc, const char** argv) {
  if (argc < 2) {
    return 1;
  }

  std::ifstream t(argv[1]);
  std::string str((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());

  datamodel::GameLevel gl = gameloader::JSON::load_game_level_from_json(str);
  datamodel::GameRun gameRun(gl);

  gamemath::Camera2D camera(datamodel::commontypes::position2d(-0.2, -0.2),
                            datamodel::units::distance(5.4), datamodel::units::distance(5.4),
                            SCREEN_WIDTH, SCREEN_HEIGHT);

  
  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    exit(1);
  }

  //Create window
  SDL_Window* window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  if( window == NULL ) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    exit(1);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  struct {
    bool w = 0;
    bool a = 0;
    bool s = 0;
    bool d = 0;
    bool q = 0;
    bool e = 0;
  } controlStates;

  while (1) {
    SDL_Event event;
    if (SDL_WaitEventTimeout(&event,1000/60)) {
      if (event.type == SDL_QUIT) {
        // Break out of the loop on quit
        break;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_w) {
          controlStates.w = 1;
        } else if (event.key.keysym.sym == SDLK_a) {
          controlStates.a = 1;
        } else if (event.key.keysym.sym == SDLK_s) {
          controlStates.s = 1;
        } else if (event.key.keysym.sym == SDLK_d) {
          controlStates.d = 1;
        } else if (event.key.keysym.sym == SDLK_q) {
          controlStates.q = 1;
        } else if (event.key.keysym.sym == SDLK_e) {
          controlStates.e = 1;
        }
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_w) {
          controlStates.w = 0;
        } else if (event.key.keysym.sym == SDLK_a) {
          controlStates.a = 0;
        } else if (event.key.keysym.sym == SDLK_s) {
          controlStates.s = 0;
        } else if (event.key.keysym.sym == SDLK_d) {
          controlStates.d = 0;
        } else if (event.key.keysym.sym == SDLK_q) {
          controlStates.q = 0;
        } else if (event.key.keysym.sym == SDLK_e) {
          controlStates.e = 0;
        }
      }
    }

    if (controlStates.w || controlStates.a || controlStates.s ||
        controlStates.d || controlStates.q || controlStates.e) {
      datamodel::GameState state = gameRun.get_state();
      datamodel::ActorData modified = *(state.data->player.data);
      if (controlStates.q) {
        modified.angle.value += 0.05;
      }
      if (controlStates.e) {
        modified.angle.value -= 0.05;
      }
      if (controlStates.w) {
        modified.pos.x.value += 0.02*std::cos(modified.angle.value);
        modified.pos.y.value += 0.02*std::sin(modified.angle.value);
      }
      if (controlStates.s) {
        modified.pos.x.value -= 0.02*std::cos(modified.angle.value);
        modified.pos.y.value -= 0.02*std::sin(modified.angle.value);
      }
      if (controlStates.a) {
        modified.pos.x.value -= 0.02*std::sin(modified.angle.value);
        modified.pos.y.value += 0.02*std::cos(modified.angle.value);
      }
      if (controlStates.d) {
        modified.pos.x.value += 0.02*std::sin(modified.angle.value);
        modified.pos.y.value -= 0.02*std::cos(modified.angle.value);
      }
      gameRun.checkpoint_state({ modified, state.data->enemies, state.data->x_size, state.data->y_size, state.data->tileset });
    }

    /* do some other stuff here -- draw your app, etc. */
    draw_frame(camera, renderer, gameRun.get_state());
  }
  
  //Destroy window
  SDL_DestroyWindow( window );

  //Quit SDL subsystems
  SDL_Quit();
  
  return 0;
}
