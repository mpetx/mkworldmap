#ifndef MKWORLDMAP_PROJECTION_HXX_2024_03_18_K7DXVLGVC2LT
#define MKWORLDMAP_PROJECTION_HXX_2024_03_18_K7DXVLGVC2LT

#include "util.hxx"

namespace mkworldmap
{

  class projection
  {
  public:

    double const x_min;
    double const x_max;
    double const y_min;
    double const y_max;

    projection() = delete;
    projection(projection const &) = default;
    projection(projection &&) = default;
    projection & operator=(projection const &) = default;
    projection & operator=(projection &&) = default;
    projection(double, double, double, double);

    double width() const;
    double height() const;

    virtual point invert(double, double) const = 0;
  };

  class equirectangular_projection : public projection
  {

  public:
    equirectangular_projection();
    equirectangular_projection(equirectangular_projection const &) = default;
    equirectangular_projection(equirectangular_projection &&) = default;
    equirectangular_projection & operator=(equirectangular_projection const &) = default;
    equirectangular_projection & operator=(equirectangular_projection &&) = default;

    point invert(double, double) const override;
  };

  class cylindrical_equal_area_projection : public projection
  {

    double s_factor;
    
  public:
    cylindrical_equal_area_projection();
    cylindrical_equal_area_projection(cylindrical_equal_area_projection const &) = default;
    cylindrical_equal_area_projection(cylindrical_equal_area_projection &&) = default;
    cylindrical_equal_area_projection & operator=(cylindrical_equal_area_projection const &) = default;
    cylindrical_equal_area_projection & operator=(cylindrical_equal_area_projection &&) = default;
    cylindrical_equal_area_projection(double);
    
    point invert(double, double) const override;
  };
  
}

#endif
