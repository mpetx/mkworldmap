
#include <cmath>
#include <numbers>

#include "projection.hxx"
#include "util.hxx"

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

  singleton_projection::singleton_projection(double x_min, double x_max, double y_min, double y_max, point (*inverter)(double, double))
    : inverter { inverter },
      projection { x_min, x_max, y_min, y_max }
  {
  }

  point singleton_projection::invert(double x, double y) const
  {
    return inverter(x, y);
  }
  
  std::unique_ptr<projection> make_simple_projection(projection_method method)
  {
    using enum projection_method;
    switch (method) {
    case equirectangular:
      return std::make_unique<singleton_projection>
	(equirectangular_x_min,
	 equirectangular_x_max,
	 equirectangular_y_min,
	 equirectangular_y_max,
	 equirectangular_invert);
    case miller:
      return std::make_unique<singleton_projection>
	(miller_x_min,
	 miller_x_max,
	 miller_y_min,
	 miller_y_max,
	 miller_invert);
    case sinusoidal:
      return std::make_unique<singleton_projection>
	(sinusoidal_x_min,
	 sinusoidal_x_max,
	 sinusoidal_y_min,
	 sinusoidal_y_max,
	 sinusoidal_invert);
    case mollweide:
      return std::make_unique<singleton_projection>
	(mollweide_x_min,
	 mollweide_x_max,
	 mollweide_y_min,
	 mollweide_y_max,
	 mollweide_invert);
    case azimuthal_equidistant:
      return std::make_unique<singleton_projection>
	(azimuthal_equidistant_x_min,
	 azimuthal_equidistant_x_max,
	 azimuthal_equidistant_y_min,
	 azimuthal_equidistant_y_max,
	 azimuthal_equidistant_invert);
    case aitoff:
      return std::make_unique<singleton_projection>
	(aitoff_x_min,
	 aitoff_x_max,
	 aitoff_y_min,
	 aitoff_y_max,
	 aitoff_invert);
    case orthographic:
      return std::make_unique<singleton_projection>
	(orthographic_x_min,
	 orthographic_x_max,
	 orthographic_y_min,
	 orthographic_y_max,
	 orthographic_invert);
    case orthographic_aitoff:
      return std::make_unique<singleton_projection>
	(orthographic_aitoff_x_min,
	 orthographic_aitoff_x_max,
	 orthographic_aitoff_y_min,
	 orthographic_aitoff_y_max,
	 orthographic_aitoff_invert);
    case lambert_azimuthal_equal_area:
      return std::make_unique<singleton_projection>
	(lambert_azimuthal_equal_area_x_min,
	 lambert_azimuthal_equal_area_x_max,
	 lambert_azimuthal_equal_area_y_min,
	 lambert_azimuthal_equal_area_y_max,
	 lambert_azimuthal_equal_area_invert);
    case hammer:
      return std::make_unique<singleton_projection>
	(hammer_x_min,
	 hammer_x_max,
	 hammer_y_min,
	 hammer_y_max,
	 hammer_invert);
    case gall_stereographic:
      return std::make_unique<singleton_projection>
	(gall_stereographic_x_min,
	 gall_stereographic_x_max,
	 gall_stereographic_y_min,
	 gall_stereographic_y_max,
	 gall_stereographic_invert);
    case eckert_1:
      return std::make_unique<singleton_projection>
	(eckert_1_x_min,
	 eckert_1_x_max,
	 eckert_1_y_min,
	 eckert_1_y_max,
	 eckert_1_invert);
    case eckert_2:
      return std::make_unique<singleton_projection>
	(eckert_2_x_min,
	 eckert_2_x_max,
	 eckert_2_y_min,
	 eckert_2_y_max,
	 eckert_2_invert);
    case eckert_3:
      return std::make_unique<singleton_projection>
	(eckert_3_x_min,
	 eckert_3_x_max,
	 eckert_3_y_min,
	 eckert_3_y_max,
	 eckert_3_invert);
    case eckert_4:
      return std::make_unique<singleton_projection>
	(eckert_4_x_min,
	 eckert_4_x_max,
	 eckert_4_y_min,
	 eckert_4_y_max,
	 eckert_4_invert);
    case eckert_5:
      return std::make_unique<singleton_projection>
	(eckert_5_x_min,
	 eckert_5_x_max,
	 eckert_5_y_min,
	 eckert_5_y_max,
	 eckert_5_invert);
    case eckert_6:
      return std::make_unique<singleton_projection>
	(eckert_6_x_min,
	 eckert_6_x_max,
	 eckert_6_y_min,
	 eckert_6_y_max,
	 eckert_6_invert);
    }
    return std::unique_ptr<projection> { };
  }

  point equirectangular_invert(double x, double y)
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

  point miller_invert(double x, double y)
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

  point sinusoidal_invert(double x, double y)
  {
    double cos = std::cos(y);
    if (x < -std::numbers::pi * cos || x > std::numbers::pi * cos)
      return point { std::nan(""), std::nan("")};
    else
      return point { x / cos, y };
  }

  point mollweide_invert(double x, double y)
  {
    double param = std::asin(y * 2 / std::numbers::pi);
    double lon = x / std::cos(param);
    if (lon < -std::numbers::pi || lon > std::numbers::pi)
      return point { std::nan(""), std::nan("") };
    double lat = std::asin((std::sin(2 * param) + 2 * param) / std::numbers::pi);
    return point { lon, lat };
  }

  point azeq_invert(double x, double y, double range)
  {
    double r = std::sqrt(x * x + y * y);
    if (r > range)
      return point { std::nan(""), std::nan("") };
    double theta = std::atan2(y, x);
    double ny = std::cos(theta + std::numbers::pi * 0.5);
    double nz = std::sin(theta + std::numbers::pi * 0.5);
    double x3 = std::cos(r);
    double y3 = nz * std::sin(r);
    double z3 = -ny * std::sin(r);
    return spacial_point_to_point(x3, y3, z3);
  }

  point azimuthal_equidistant_invert(double x, double y)
  {
    return azeq_invert(x, y, std::numbers::pi);
  }

  point aitoff_invert(double x, double y)
  {
    point p = azeq_invert(x * 0.5, y, std::numbers::pi * 0.5);
    p.x *= 2;
    return p;
  }

  point orthographic_invert(double x, double y)
  {
    if (x * x + y * y > 1)
      return point { std::nan(""), std::nan("") };
    return point {
      std::asin(x / std::sqrt(1 - y * y)),
      std::asin(y)
    };
  }

  point orthographic_aitoff_invert(double x, double y)
  {
    point p = orthographic_invert(x * 0.5, y);
    p.x *= 2;
    return p;
  }

  point laea_invert(double x, double y, double range)
  {
    double r = std::sqrt(x * x + y * y);
    double nr = 2 * std::asin(r / 2.0);
    if (nr > range)
      return point { std::nan(""), std::nan("") };
    double theta = std::atan2(y, x);
    double ny = std::cos(theta + std::numbers::pi * 0.5);
    double nz = std::sin(theta + std::numbers::pi * 0.5);
    double x3 = std::cos(nr);
    double y3 = nz * std::sin(nr);
    double z3 = -ny * std::sin(nr);
    return spacial_point_to_point(x3, y3, z3);
  }

  point lambert_azimuthal_equal_area_invert(double x, double y)
  {
    return laea_invert(x, y, std::numbers::pi);
  }

  point hammer_invert(double x, double y)
  {
    point p = laea_invert(x * 0.5, y, std::numbers::pi * 0.5);
    p.x *= 2;
    return p;
  }

  point gall_stereographic_invert(double x, double y)
  {
    return point {
      x,
      2 * std::atan(y / (std::sqrt(2) + 1))
    };
  }

  point eckert_1_invert(double x, double y)
  {
    double factor = 1 - std::abs(y) / std::numbers::pi;
    if (x < -std::numbers::pi * factor || x > std::numbers::pi * factor)
      return point { std::nan(""), std::nan("") };
    return point { x / factor, y };
  }

  point eckert_2_invert(double x, double y)
  {
    double factor = 2 - std::abs(y);
    if (x < -factor || x > factor)
      return point { std::nan(""), std::nan("") };
    return point {
      x * std::numbers::pi / factor,
      sign(y) * std::asin((4 - factor * factor) / 3)
    };
  }

  point eckert_3_invert(double x, double y)
  {
    double factor = 1 + std::sqrt(1 - y * y / (std::numbers::pi * std::numbers::pi));
    if (x < -std::numbers::pi * factor || x > std::numbers::pi * factor)
      return point { std::nan(""), std::nan("") };
    return point {
      x / factor,
      y / 2
    };
  }

  point eckert_4_invert(double x, double y)
  {
    double param = std::asin(y / std::numbers::pi);
    double factor = 1 + std::cos(param);
    if (x < - std::numbers::pi * factor || x > std::numbers::pi * factor)
      return point { std::nan(""), std::nan("") };
    return point {
      x / factor,
      std::asin((param + std::sin(param) * std::cos(param) + 2 * std::sin(param)) / (2 + std::numbers::pi / 2))
    };
  }

  point eckert_5_invert(double x, double y)
  {
    double factor = 1 + std::cos(y / 2);
    if (x < - std::numbers::pi * factor || x > std::numbers::pi * factor)
      return point { std::nan(""), std::nan("") };
    return point {
      x / factor,
      y / 2
    };
  }

  point eckert_6_invert(double x, double y)
  {
    double factor = 1 + std::cos(y / 2);
    if (x < - std::numbers::pi * factor || x > std::numbers::pi * factor)
      return point { std::nan(""), std::nan("") };
    return point {
      x / factor,
      std::asin((y / 2 + std::sin(y / 2)) / (1 + std::numbers::pi / 2))
    };
  }

}
