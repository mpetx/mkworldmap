
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

  std::unique_ptr<projection> make_simple_projection(projection_method method)
  {
    using enum projection_method;
    switch (method) {
    case equirectangular:
      return std::make_unique<simple_projection<equirectangular>>();
    case miller:
      return std::make_unique<simple_projection<miller>>();
    case sinusoidal:
      return std::make_unique<simple_projection<sinusoidal>>();
    case mollweide:
      return std::make_unique<simple_projection<mollweide>>();
    case azimuthal_equidistant:
      return std::make_unique<simple_projection<azimuthal_equidistant>>();
    case aitoff:
      return std::make_unique<simple_projection<aitoff>>();
    case orthographic:
      return std::make_unique<simple_projection<orthographic>>();
    case orthographic_aitoff:
      return std::make_unique<simple_projection<orthographic_aitoff>>();
    case lambert_azimuthal_equal_area:
      return std::make_unique<simple_projection<lambert_azimuthal_equal_area>>();
    case hammer:
      return std::make_unique<simple_projection<hammer>>();
    case gall_stereographic:
      return std::make_unique<simple_projection<gall_stereographic>>();
    }
    return std::unique_ptr<projection> { };
  }

  template <>
  simple_projection<projection_method::equirectangular>::simple_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::numbers::pi * 0.5,
	std::numbers::pi * 0.5
      }
  {
  }

  template <>
  point simple_projection<projection_method::equirectangular>::invert(double x, double y) const
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

  template <>
  simple_projection<projection_method::miller>::simple_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-1.25 * inverse_gudermann(0.4 * std::numbers::pi),
	1.25 * inverse_gudermann(0.4 * std::numbers::pi)
      }
  {
  }

  template <>
  point simple_projection<projection_method::miller>::invert(double x, double y) const
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

  template <>
  simple_projection<projection_method::sinusoidal>::simple_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::numbers::pi * 0.5,
	std::numbers::pi * 0.5
      }
  {
  }

  template <>
  point simple_projection<projection_method::sinusoidal>::invert(double x, double y) const
  {
    double cos = std::cos(y);
    if (x < -std::numbers::pi * cos || x > std::numbers::pi * cos)
      return point { std::nan(""), std::nan("")};
    else
      return point { x / cos, y };
  }

  template <>
  simple_projection<projection_method::mollweide>::simple_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::numbers::pi * 0.5,
	std::numbers::pi * 0.5
      }
  {
  }

  template <>
  point simple_projection<projection_method::mollweide>::invert(double x, double y) const
  {
    double param = std::asin(y * 2 / std::numbers::pi);
    double lon = x / std::cos(param);
    if (lon < -std::numbers::pi || lon > std::numbers::pi)
      return point { std::nan(""), std::nan("") };
    double lat = std::asin((std::sin(2 * param) + 2 * param) / std::numbers::pi);
    return point { lon, lat };
  }

  template <>
  simple_projection<projection_method::azimuthal_equidistant>::simple_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::numbers::pi,
	std::numbers::pi
      }
  {
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

  template <>
  point simple_projection<projection_method::azimuthal_equidistant>::invert(double x, double y) const
  {
    return azeq_invert(x, y, std::numbers::pi);
  }

  template <>
  simple_projection<projection_method::aitoff>::simple_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::numbers::pi * 0.5,
	std::numbers::pi * 0.5
      }
  {
  }

  template <>
  point simple_projection<projection_method::aitoff>::invert(double x, double y) const
  {
    point p = azeq_invert(x * 0.5, y, std::numbers::pi * 0.5);
    p.x *= 2;
    return p;
  }

  template <>
  simple_projection<projection_method::orthographic>::simple_projection()
    : projection {
	-1, 1, -1, 1
      }
  {
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

  template <>
  point simple_projection<projection_method::orthographic>::invert(double x, double y) const
  {
    return orthographic_invert(x, y);
  }

  template <>
  simple_projection<projection_method::orthographic_aitoff>::simple_projection()
    : projection {
	-2, 2, -1, 1
      }
  {
  }

  template <>
  point simple_projection<projection_method::orthographic_aitoff>::invert(double x, double y) const
  {
    point p = orthographic_invert(x * 0.5, y);
    p.x *= 2;
    return p;
  }

  template <>
  simple_projection<projection_method::lambert_azimuthal_equal_area>::simple_projection()
    : projection {
	-2, 2, -2, 2
      }
  {
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

  template <>
  point simple_projection<projection_method::lambert_azimuthal_equal_area>::invert(double x, double y) const
  {
    return laea_invert(x, y, std::numbers::pi);
  }

  template <>
  simple_projection<projection_method::hammer>::simple_projection()
    : projection {
	-2 * std::sqrt(2),
	2 * std::sqrt(2),
	-std::sqrt(2),
	std::sqrt(2)
      }
  {
  }

  template <>
  point simple_projection<projection_method::hammer>::invert(double x, double y) const
  {
    point p = laea_invert(x * 0.5, y, std::numbers::pi * 0.5);
    p.x *= 2;
    return p;
  }

  template <>
  simple_projection<projection_method::gall_stereographic>::simple_projection()
    : projection {
	-std::numbers::pi,
	std::numbers::pi,
	-std::sqrt(2) - 1,
	std::sqrt(2) + 1
      }
  {
  }

  template <>
  point simple_projection<projection_method::gall_stereographic>::invert(double x, double y) const
  {
    return point {
      x,
      2 * std::atan(y / (std::sqrt(2) + 1))
    };
  }

}
