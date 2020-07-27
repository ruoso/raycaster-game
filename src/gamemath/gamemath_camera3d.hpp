#ifndef INCLUDED_GAMEMATH_CAMERA3D_HPP
#define INCLUDED_GAMEMATH_CAMERA3D_HPP

#include <variant>
#include <datamodel_commontypes.hpp>
#include <datamodel_units.hpp>
#include <gamemath_raycast.hpp>

namespace raycaster {
  namespace gamemath {

    typedef std::tuple<int, int, datamodel::units::distance, raycast_hit>
    Camera3DHit;

    typedef std::vector<Camera3DHit>
    Camera3DSlice;

    typedef std::vector<Camera3DSlice>
    Camera3DRender;

    class Camera3D {
      datamodel::units::angle x_fov;
      datamodel::units::angle z_fov;
      datamodel::units::distance wall_height;
      datamodel::units::distance enemy_height;
      int pixels_x_size;
      int pixels_y_size;
      datamodel::units::angle ray_angle_step;
      
    public:
      Camera3D(datamodel::units::angle _x_fov,
               datamodel::units::angle _z_fov,
               datamodel::units::distance _wall_height,
               datamodel::units::distance _enemy_height,
               int _pixels_x_size,
               int _pixels_y_size) :x_fov(_x_fov), z_fov(_z_fov),
                                    wall_height(_wall_height), enemy_height(_enemy_height),
                                    pixels_x_size(_pixels_x_size), pixels_y_size(_pixels_y_size),
                                    ray_angle_step(_x_fov.value / pixels_x_size) {}

      const Camera3DRender
      render_slices(datamodel::commontypes::position2d pos,
                    datamodel::units::angle angle,
                    const datamodel::GameState state) {
        Camera3DRender ret;
        const datamodel::GameStateData data = *(state.data);
        datamodel::units::angle start_a(angle.value + x_fov.value/2);
        datamodel::units::angle end_a(angle.value - x_fov.value/2);
        for (datamodel::units::angle w_a = start_a; w_a >= end_a; w_a -= ray_angle_step) {
          Camera3DSlice slice;
          datamodel::commontypes::position2d end( std::cos(w_a.value) * data.x_size * data.y_size,
                                                  std::sin(w_a.value) * data.x_size * data.y_size);
          raycast_hits ray_hits =
            raycast(pos, end, state, 1);
          for ( raycast_hit ray_hit : ray_hits ) {
            const datamodel::commontypes::position2d& ray_hit_pos = std::get<0>(ray_hit);
            double offset_x = std::abs(ray_hit_pos.x.value - pos.x.value);
            double offset_y = std::abs(ray_hit_pos.y.value - pos.y.value);
            double height;
            if (std::get<1>(ray_hit).index() == 0) {
              height = enemy_height.value;
            } else {
              height = wall_height.value;
            }
            datamodel::units::distance d(std::sqrt(offset_x*offset_x + offset_y*offset_y));
            datamodel::units::angle a_wall(std::atan(height/d.value)*2);
            double ratio = a_wall.value / z_fov.value;
            int z = int(pixels_y_size * ratio);
            int low_z = pixels_y_size/2 + z/2;
            int high_z = pixels_y_size/2 - z/2;
            Camera3DHit hit(low_z, high_z, d, ray_hit);
            slice.push_back(hit);
          }
            
          ret.push_back(slice);
        }

        return ret;
      }
    };
  }
}

#endif
