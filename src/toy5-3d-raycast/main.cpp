#include <iostream>

#include <cmath>
#include <string>
#include <fstream>
#include <streambuf>

#include <SDL.h>

#include <gameloader_json.hpp>
#include <gamemath_raycast.hpp>
#include <datamodel_commontypes.hpp>
#include <gamemath_camera3d.hpp>
#include <datamodel_gamerun.hpp>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

using namespace raycaster;

void draw_frame(gamemath::Camera3D& camera, SDL_Renderer* renderer, datamodel::GameState s) {
  //Fill the surface white
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);
  SDL_RenderClear(renderer);
  const datamodel::Actor& player = s.data->player;
  const datamodel::commontypes::position2d& pos = player.data->pos;
  const datamodel::units::angle angle = player.data->angle;
  
  gamemath::Camera3DRender render = camera.render_slices(pos, angle, s);
  int x_count = 0;
  for (gamemath::Camera3DSlice slice : render) {
    for (gamemath::Camera3DSlice::reverse_iterator hit_it = slice.rbegin(); hit_it != slice.rend(); ++hit_it) {
      const gamemath::Camera3DHit& hit = *hit_it;
      int low_z = std::get<0>(hit);
      int high_z = std::get<1>(hit);
      const datamodel::units::distance& d = std::get<2>(hit);
      const gamemath::raycast_hit& ray_hit = std::get<3>(hit);
      const gamemath::raycast_hit_type& ray_hit_type = std::get<1>(ray_hit);
      int c = d.value*10;
      if (c > 100) {
        c = 100;
      }
      if (ray_hit_type.index() == 0) {
        SDL_SetRenderDrawColor(renderer, 95 - c, 0, 0, 50);
      } else {
        SDL_SetRenderDrawColor(renderer, 100 - c, 100 - c, 100 - c, 50);
      }
      SDL_RenderDrawLine( renderer,
                          x_count, low_z,
                          x_count, high_z );
    }
    x_count++;
  }

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

  gamemath::Camera3D camera(std::acos(-1)/2, std::acos(-1)/2, 1, 0.4, SCREEN_WIDTH, SCREEN_HEIGHT);

  
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
