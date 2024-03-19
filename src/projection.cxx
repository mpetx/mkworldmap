
#include <cmath>
#include <numbers>

#include "projection.hxx"

namespace mkworldmap
{

  projection::projection(double x_min_, double x_max_, double y_min_, double y_max_)
    : x_min { x_min_ },
      x_max { x_max_ },
      y_min { y_min_ },
      y_max { y_max_ }
  {
  }

  double projection::width() const
  {
    return x_max - x_min;
  }

  double projection::height() const
  {
    return y_max - y_min;
  }

  equirectangular_projection::equirectangular_projection()
    : projection { -std::numbers::pi, std::numbers::pi, -std::numbers::pi * 0.5, std::numbers::pi * 0.5 }
  {
  }

  point equirectangular_projection::invert(double x, double y) const
  {
    return point { x, y };
  }

  cylindrical_equal_area_projection::cylindrical_equal_area_projection()
    : cylindrical_equal_area_projection { 0 }
  {
  }

  cylindrical_equal_area_projection::cylindrical_equal_area_projection(double sl)
    : s_factor { std::cos(sl) },
      projection {
	-std::cos(sl) * std::numbers::pi,
	std::cos(sl) * std::numbers::pi,
	-1 / std::cos(sl),
	1 / std::cos(sl)
      }
  {
  }

  point cylindrical_equal_area_projection::invert(double x, double y) const
  {
    return point {
      x / s_factor,
      std::asin(y * s_factor)
    };
  }

  double gudermann(double x)
  {
    return std::asin(std::tanh(x));
  }

  double inverse_gudermann(double x)
  {
    return std::atanh(std::sin(x));
  }
  
  mercator_projection::mercator_projection(double max_latitude_)
    : max_latitude { max_latitude_ },
      projection {
	-std::numbers::pi,
	std::numbers::pi,
	-inverse_gudermann(max_latitude_),
	inverse_gudermann(max_latitude_)
      }
  {
  }

  point mercator_projection::invert(double x, double y) const
  {
    return point {
      x,
      gudermann(y)
    };
  }

  miller_projection::miller_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-1.25 * inverse_gudermann(0.4 * std::numbers::pi),
	1.25 * inverse_gudermann(0.4 * std::numbers::pi)
      }
  {
  }

  point miller_projection::invert(double x, double y) const
  {
    return point {
      x,
      1.25 * gudermann(0.8 * y)
    };
  }

  central_cylindrical_projection::central_cylindrical_projection(double max_latitude_)
    : max_latitude { max_latitude_ },
      projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::tan(max_latitude_),
	std::tan(max_latitude_)
      }
  {
  }

  point central_cylindrical_projection::invert(double x, double y) const
  {
    return point {
      x,
      std::atan(y)
    };
  }

  sinusoidal_projection::sinusoidal_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::numbers::pi * 0.5,
	std::numbers::pi * 0.5
      }
  {
  }

  point sinusoidal_projection::invert(double x, double y) const
  {
    double cos = std::cos(y);
    if (x < -std::numbers::pi * cos || x > std::numbers::pi * cos)
      return point {
	std::nan(""),
	std::nan("")
      };
    else
      return point {
	x / cos,
	y
      };
  }

  mollweide_projection::mollweide_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::numbers::pi * 0.5,
	std::numbers::pi * 0.5
      }
  {
  }

  point mollweide_projection::invert(double x, double y) const
  {
    double param = std::asin(y * 2 / std::numbers::pi);
    double lon = x / std::cos(param);
    if (lon < -std::numbers::pi || lon > std::numbers::pi)
      return point { std::nan(""), std::nan("") };
    double lat = std::asin((std::sin(2 * param) + 2 * param) / std::numbers::pi);
    return point { lon, lat };
  }
  
}
