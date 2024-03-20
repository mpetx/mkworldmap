#ifndef MKWORLDMAP_UTIL_HXX_2024_03_18_26AWGQH5NJ4S
#define MKWORLDMAP_UTIL_HXX_2024_03_18_26AWGQH5NJ4S

#include <cmath>

namespace mkworldmap
{
  struct color
  {
    char unsigned red;
    char unsigned green;
    char unsigned blue;
  };

  struct point
  {
    double x;
    double y;
  };
  
  inline double clamp(double x, double lower_bound, double upper_bound)
  {
    if (x < lower_bound)
      return lower_bound;
    else if (x > upper_bound)
      return upper_bound;
    else
      return x;
  }

  inline point spacial_point_to_point(double x, double y, double z)
  {
    return point {
      std::atan2(y, x),
      std::atan2(z, std::sqrt(x * x + y * y))
    };
  }

  template <typename T>
  T sign(T x)
  {
    if (x > 0)
      return static_cast<T>(1);
    else if (x < 0)
      return static_cast<T>(-1);
    else
      return 0;
  }
  
}

#endif
