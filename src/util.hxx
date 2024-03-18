#ifndef MKWORLDMAP_UTIL_HXX_2024_03_18_26AWGQH5NJ4S
#define MKWORLDMAP_UTIL_HXX_2024_03_18_26AWGQH5NJ4S

namespace mkworldmap
{
  struct color
  {
    char unsigned red;
    char unsigned green;
    char unsigned blue;
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
}

#endif
