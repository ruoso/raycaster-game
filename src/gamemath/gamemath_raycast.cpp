#include "gamemath_raycast.hpp"
#include "gamemath_distances.hpp"

namespace raycaster {
  namespace gamemath {

    static const datamodel::units::angle deg0(0.0);
    static const datamodel::units::angle deg180(std::acos(-1));
    static const datamodel::units::angle deg360(deg180.value*2);
    static const datamodel::units::angle deg90(deg180.value/2);
    static const datamodel::units::angle deg270(deg180.value + deg180.value/2);

    
    static std::tuple<double, double>
    rotated_hit_point(double angle_v, double max_0deg, double max_90deg) {
      double offset_90deg = std::tan(angle_v) * max_0deg;
      double hit_0deg, hit_90deg;
      if (offset_90deg <= max_90deg) {
        // the triangle fits with the 0-degrees distance
        hit_0deg = std::nexttoward(max_0deg, max_0deg + 1);
        hit_90deg = offset_90deg;
      } else {
        // the triangle doesn't fit when we use the max_0deg distance,
        // so let's do it with the max_90deg distance instead
        hit_0deg = max_90deg / std::tan(angle_v);
        hit_90deg = std::nexttoward(max_90deg, max_90deg + 1);
      }
      return std::tuple<double,double>(hit_0deg, hit_90deg);
    }
    
    static void
    check_enemy_collision(const std::vector<datamodel::Actor>& candidate_enemies,
                          double curr_x, double curr_y,
                          double next_x, double next_y,
                          raycast_hits& ret) {
      for ( const datamodel::Actor& a : candidate_enemies ) {
        const std::shared_ptr<const datamodel::ActorData> data = a.data;
        const datamodel::commontypes::position2d& pos = data->pos;
        double radius = data->radius;
        if ( pos.x + radius >= std::min(curr_x, next_x) &&
             pos.x - radius <= std::max(curr_x, next_x) &&
             pos.y + radius >= std::min(curr_y, next_y) &&
             pos.y - radius <= std::max(curr_y, next_y)) {
          datamodel::commontypes::position2d c =
            closest_from_point_to_line_segment(pos,
                                               datamodel::commontypes::position2d(curr_x, curr_y),
                                               datamodel::commontypes::position2d(next_x, next_y));
          datamodel::units::distance d =
            distance_between_positions(pos, c);
          
          if (d.value < radius) {
            // enemy collision in point c
          }
        }
      }
    }

    raycast_hits raycast(const datamodel::commontypes::position2d& start,
                         const datamodel::commontypes::position2d& end,
                         const datamodel::GameState& state,
                         const int& max_wall_hits) {
      int wall_hits = 0;
      
      int start_tile_x = int(start.x.value);
      int start_tile_y = int(start.y.value);
      int end_tile_x = int(end.x.value);
      int end_tile_y = int(end.y.value);
      int max_x = state.data->x_size + 1;
      int max_y = state.data->y_size + 1;

      int curr_tile_x = start_tile_x;
      int curr_tile_y = start_tile_y;
      double curr_x = start.x.value;
      double curr_y = start.y.value;

      double delta_x = start.x.value - end.x.value;
      double delta_y = start.y.value - end.y.value;
      datamodel::units::angle angle(std::atan2(delta_y, delta_x));

      std::vector<datamodel::Actor> candidate_enemies;
      for ( const datamodel::Actor& a : state.data->enemies ) {
        const std::shared_ptr<const datamodel::ActorData> data = a.data;
        const datamodel::commontypes::position2d& pos = data->pos;
        double radius = data->radius;
        if ( pos.x + radius >= std::min(start.x.value, end.x.value) &&
             pos.x - radius <= std::max(start.x.value, end.x.value) &&
             pos.y + radius >= std::min(start.y.value, end.y.value) &&
             pos.y - radius <= std::max(start.y.value, end.y.value)) {
          candidate_enemies.push_back(a);
        }
      }
      
      raycast_hits ret;
      while (curr_tile_x != end_tile_x && curr_tile_y != end_tile_y &&
             curr_tile_x < max_x && curr_tile_y < max_y &&
             curr_tile_x >= 0 && curr_tile_y >= 0) {
        // find the closest point between curr_x,curr_y and the tile border
        double next_x, next_y;
        if (angle == deg0 || angle == deg360) {
          next_x = curr_tile_x+1;
          next_y = curr_y;
        } else if (angle == deg90) {
          next_x = curr_x;
          next_y = curr_tile_y+1;
        } else if (angle == deg180) {
          next_x = std::nexttoward(curr_tile_x, curr_tile_x - 1);
          next_y = curr_y;
        } else if (angle == deg270) {
          next_x = curr_x;
          next_y = std::nexttoward(curr_tile_y, curr_tile_y - 1);
        } else {

          if (angle < deg90) {
            std::tuple<double, double> hits =
              rotated_hit_point(angle.value,
                                curr_tile_x + 1 - curr_x,
                                curr_tile_y + 1 - curr_y);
            next_x = curr_x + std::get<0>(hits);
            next_y = curr_y + std::get<1>(hits);

          } else if (angle < deg180) {
            std::tuple<double, double> hits =
              rotated_hit_point(angle.value - deg90.value,
                                curr_tile_y + 1 - curr_y,
                                curr_x - curr_tile_x);
            next_y = curr_y + std::get<0>(hits);
            next_x = curr_x - std::get<1>(hits);

          } else if (angle < deg270) {
            std::tuple<double, double> hits =
              rotated_hit_point(angle.value - deg180.value,
                                curr_x - curr_tile_x,
                                curr_y - curr_tile_y);
            next_x = curr_x - std::get<0>(hits);
            next_y = curr_y - std::get<1>(hits);

          } else {
            std::tuple<double, double> hits =
              rotated_hit_point(angle.value - deg270.value,
                                curr_tile_x + 1 - curr_x,
                                curr_y - curr_tile_y);
            next_x = curr_x + std::get<0>(hits);
            next_y = curr_y - std::get<1>(hits);

          }
        }

        check_enemy_collision(candidate_enemies, curr_x, curr_y, next_x, next_y, ret);
        
        int next_tile_x = int(next_x);
        int next_tile_y = int(next_y);

        const datamodel::Tile curr_tile = state.tile_at(curr_tile_x, curr_tile_y);
        uint8_t curr_wall = curr_tile.data->current_state->data->wall_collision_map;
        const datamodel::Tile next_tile = state.tile_at(next_tile_x, next_tile_y);
        uint8_t next_wall = next_tile.data->current_state->data->wall_collision_map;

        if (next_tile_x > curr_tile_x) {
          if (curr_wall & datamodel::WALL_COLLIDE_EAST) {
            // collision
            if (++wall_hits >= max_wall_hits)
              break;
          }
          if (next_wall & datamodel::WALL_COLLIDE_WEST) {
            // collision
            if (++wall_hits >= max_wall_hits)
              break;
          }

        } else if (next_tile_x < curr_tile_x) {
          if (curr_wall & datamodel::WALL_COLLIDE_WEST) {
            // collision
            if (++wall_hits >= max_wall_hits)
              break;
          }
          if (next_wall & datamodel::WALL_COLLIDE_EAST) {
            // collision
            if (++wall_hits >= max_wall_hits)
              break;
          }
         
        }

        if (next_tile_y > curr_tile_y) {
          if (curr_wall & datamodel::WALL_COLLIDE_NORTH) {
            // collision
            if (++wall_hits >= max_wall_hits)
              break;
          }
          if (next_wall & datamodel::WALL_COLLIDE_SOUTH) {
            // collision
            if (++wall_hits >= max_wall_hits)
              break;
          }

        } else if (next_tile_y < curr_tile_y) {
          if (curr_wall & datamodel::WALL_COLLIDE_SOUTH) {
            // collision
            if (++wall_hits >= max_wall_hits)
              break;
          }
          if (next_wall & datamodel::WALL_COLLIDE_NORTH) {
            // collision
            if (++wall_hits >= max_wall_hits)
              break;
          }
         
        }
        
        curr_tile_x = next_tile_x;
        curr_tile_y = next_tile_y;
        curr_x = next_x;
        curr_y = next_y;
      }
      if (end_tile_x >= 0 && end_tile_x < max_x &&
          end_tile_y >= 0 && end_tile_y < max_y &&
          curr_tile_x == end_tile_x &&
          curr_tile_y == end_tile_y) {
        // check for colision within the tile
        check_enemy_collision(candidate_enemies, curr_x, curr_y, end.x.value, end.y.value, ret);
      }

      return ret;
    }

  }
}
