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

  double gudermann(double x);
  
  class mercator_projection : public projection
  {
    double max_latitude;
    
  public:
    mercator_projection() = delete;
    mercator_projection(mercator_projection const &) = default;
    mercator_projection(mercator_projection &&) = default;
    mercator_projection & operator=(mercator_projection const &) = default;
    mercator_projection & operator=(mercator_projection &&) = default;
    mercator_projection(double);
    
    point invert(double, double) const override;
  };

  class miller_projection : public projection
  {
  public:
    miller_projection();
    miller_projection(miller_projection const &) = default;
    miller_projection(miller_projection &&) = default;
    miller_projection & operator=(miller_projection const &) = default;
    miller_projection & operator=(miller_projection &&) = default;
    
    point invert(double, double) const override;
  };

  class central_cylindrical_projection : public projection
  {
    double max_latitude;
    
  public:
    central_cylindrical_projection() = delete;
    central_cylindrical_projection(central_cylindrical_projection const &) = default;
    central_cylindrical_projection(central_cylindrical_projection &&) = default;
    central_cylindrical_projection & operator=(central_cylindrical_projection const &) = default;
    central_cylindrical_projection & operator=(central_cylindrical_projection &&) = default;
    central_cylindrical_projection(double);
    
    point invert(double, double) const override;
  };

  class sinusoidal_projection : public projection
  {
  public:
    sinusoidal_projection();
    sinusoidal_projection(sinusoidal_projection const &) = default;
    sinusoidal_projection(sinusoidal_projection &&) = default;
    sinusoidal_projection & operator=(sinusoidal_projection const &) = default;
    sinusoidal_projection & operator=(sinusoidal_projection &&) = default;
    
    point invert(double, double) const override;
  };

  class mollweide_projection : public projection
  {
  public:
    mollweide_projection();
    mollweide_projection(mollweide_projection const &) = default;
    mollweide_projection(mollweide_projection &&) = default;
    mollweide_projection & operator=(mollweide_projection const &) = default;
    mollweide_projection & operator=(mollweide_projection &&) = default;
    
    point invert(double, double) const override;
  };
  
}

#endif
