#ifndef INCLUDED_GAMEMATH_CAMERA2D_HPP
#define INCLUDED_GAMEMATH_CAMERA2D_HPP

#include <variant>
#include <datamodel_commontypes.hpp>
#include <datamodel_units.hpp>

namespace raycaster {
  namespace gamemath {

    struct Camera2DPixelPosition {
      int x = 0;
      int y = 0;
    };

    class Camera2D {
      datamodel::commontypes::position2d origin;
      datamodel::units::distance real_x_size;
      datamodel::units::distance real_y_size;
      int pixels_x_size;
      int pixels_y_size;
      double x_scale;
      double y_scale;

    public:
      Camera2D(datamodel::commontypes::position2d _origin,
               datamodel::units::distance _real_x_size,
               datamodel::units::distance _real_y_size,
               int _pixels_x_size,
               int _pixels_y_size) :origin(_origin),
                                    real_x_size(_real_x_size), real_y_size(_real_y_size),
                                    pixels_x_size(_pixels_x_size), pixels_y_size(_pixels_y_size),
                                    x_scale(_pixels_x_size / _real_x_size.value),
                                    y_scale(_pixels_y_size / _real_y_size.value) {}

      
      Camera2DPixelPosition
      point_to_pixel(const datamodel::commontypes::position2d& point) const {
        int pixel_x = int(std::round(point.x.value * x_scale - origin.x.value * x_scale));
        int pixel_y = pixels_y_size - int(std::round(point.y.value * y_scale - origin.y.value * y_scale));
        return Camera2DPixelPosition({ pixel_x, pixel_y });
      }
    };
  }
}

#endif
