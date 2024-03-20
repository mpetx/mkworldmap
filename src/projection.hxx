#ifndef MKWORLDMAP_PROJECTION_HXX_2024_03_18_K7DXVLGVC2LT
#define MKWORLDMAP_PROJECTION_HXX_2024_03_18_K7DXVLGVC2LT

#include <memory>

#include "util.hxx"

namespace mkworldmap
{
  
  enum class projection_method
  {
    equirectangular,
    cylindrical_equal_area,
    mercator,
    miller,
    central_cylindrical,
    sinusoidal,
    mollweide,
    azimuthal_equidistant,
    aitoff,
    orthographic,
    orthographic_aitoff,
    lambert_azimuthal_equal_area,
    hammer,
    gall_stereographic,
    eckert_1,
    eckert_2,
    eckert_3,
    eckert_4,
    eckert_5,
    eckert_6,
    invalid
  };

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

  template <projection_method type>
  class simple_projection : public projection
  {
  public:
    simple_projection();
    simple_projection(simple_projection const &) = default;
    simple_projection(simple_projection &&) = default;
    simple_projection & operator=(simple_projection const &) = default;
    simple_projection & operator=(simple_projection &&) = default;

    point invert(double, double) const override;
  };

  std::unique_ptr<projection> make_simple_projection(projection_method);
  
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

}

#endif
