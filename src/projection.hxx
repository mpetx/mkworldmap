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
    collignon,
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

  class singleton_projection : public projection
  {

    point (*inverter)(double, double);
  public:
    singleton_projection() = delete;
    singleton_projection(singleton_projection const &) = default;
    singleton_projection(singleton_projection &&) = default;
    singleton_projection & operator=(singleton_projection const &) = default;
    singleton_projection & operator=(singleton_projection &&) = default;
    singleton_projection(double, double, double, double, point (*)(double, double));

    point invert(double, double) const override;
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

  constexpr double gudermann(double x)
  {
    return std::asin(std::tanh(x));
  }
    
  constexpr double inverse_gudermann(double x)
  {
    return std::atanh(std::sin(x));
  }

  double constexpr equirectangular_x_min = -std::numbers::pi;
  double constexpr equirectangular_x_max = std::numbers::pi;
  double constexpr equirectangular_y_min = -std::numbers::pi * 0.5;
  double constexpr equirectangular_y_max = std::numbers::pi * 0.5;
  point equirectangular_invert(double, double);

  double constexpr miller_x_min = -std::numbers::pi;
  double constexpr miller_x_max = std::numbers::pi;
  double constexpr miller_y_min = -1.25 * inverse_gudermann(0.4 * std::numbers::pi);
  double constexpr miller_y_max = 1.25 * inverse_gudermann(0.4 * std::numbers::pi);
  point miller_invert(double, double);

  double constexpr sinusoidal_x_min = -std::numbers::pi;
  double constexpr sinusoidal_x_max = std::numbers::pi;
  double constexpr sinusoidal_y_min = -std::numbers::pi * 0.5;
  double constexpr sinusoidal_y_max = std::numbers::pi * 0.5;
  point sinusoidal_invert(double, double);

  double constexpr mollweide_x_min = -std::numbers::pi;
  double constexpr mollweide_x_max = std::numbers::pi;
  double constexpr mollweide_y_min = -std::numbers::pi * 0.5;
  double constexpr mollweide_y_max = std::numbers::pi * 0.5;
  point mollweide_invert(double, double);

  double constexpr azimuthal_equidistant_x_min = -std::numbers::pi;
  double constexpr azimuthal_equidistant_x_max = std::numbers::pi;
  double constexpr azimuthal_equidistant_y_min = -std::numbers::pi;
  double constexpr azimuthal_equidistant_y_max = std::numbers::pi;
  point azimuthal_equidistant_invert(double, double);

  double constexpr aitoff_x_min = -std::numbers::pi;
  double constexpr aitoff_x_max = std::numbers::pi;
  double constexpr aitoff_y_min = -std::numbers::pi * 0.5;
  double constexpr aitoff_y_max = std::numbers::pi * 0.5;
  point aitoff_invert(double, double);

  double constexpr orthographic_x_min = -1;
  double constexpr orthographic_x_max = 1;
  double constexpr orthographic_y_min = -1;
  double constexpr orthographic_y_max = 1;
  point orthographic_invert(double, double);

  double constexpr orthographic_aitoff_x_min = -2;
  double constexpr orthographic_aitoff_x_max = 2;
  double constexpr orthographic_aitoff_y_min = -1;
  double constexpr orthographic_aitoff_y_max = 1;
  point orthographic_aitoff_invert(double, double);

  double constexpr lambert_azimuthal_equal_area_x_min = -2;
  double constexpr lambert_azimuthal_equal_area_x_max = 2;
  double constexpr lambert_azimuthal_equal_area_y_min = -2;
  double constexpr lambert_azimuthal_equal_area_y_max = 2;
  point lambert_azimuthal_equal_area_invert(double, double);

  double constexpr hammer_x_min = -2 * std::sqrt(2);
  double constexpr hammer_x_max = 2 * std::sqrt(2);
  double constexpr hammer_y_min = -std::sqrt(2);
  double constexpr hammer_y_max = std::sqrt(2);
  point hammer_invert(double, double);

  double constexpr gall_stereographic_x_min = -std::numbers::pi;
  double constexpr gall_stereographic_x_max = std::numbers::pi;
  double constexpr gall_stereographic_y_min = -std::sqrt(2) - 1;
  double constexpr gall_stereographic_y_max = std::sqrt(2) + 1;
  point gall_stereographic_invert(double, double);

  double constexpr eckert_1_x_min = -std::numbers::pi;
  double constexpr eckert_1_x_max = std::numbers::pi;
  double constexpr eckert_1_y_min = -std::numbers::pi * 0.5;
  double constexpr eckert_1_y_max = std::numbers::pi * 0.5;
  point eckert_1_invert(double, double);

  double constexpr eckert_2_x_min = -2;
  double constexpr eckert_2_x_max = 2;
  double constexpr eckert_2_y_min = -1;
  double constexpr eckert_2_y_max = 1;
  point eckert_2_invert(double, double);

  double constexpr eckert_3_x_min = -2 * std::numbers::pi;
  double constexpr eckert_3_x_max = 2 * std::numbers::pi;
  double constexpr eckert_3_y_min = -std::numbers::pi;
  double constexpr eckert_3_y_max = std::numbers::pi;
  point eckert_3_invert(double, double);

  double constexpr eckert_4_x_min = -2 * std::numbers::pi;
  double constexpr eckert_4_x_max = 2 * std::numbers::pi;
  double constexpr eckert_4_y_min = -std::numbers::pi;
  double constexpr eckert_4_y_max = std::numbers::pi;
  point eckert_4_invert(double, double);

  double constexpr eckert_5_x_min = -2 * std::numbers::pi;
  double constexpr eckert_5_x_max = 2 * std::numbers::pi;
  double constexpr eckert_5_y_min = -std::numbers::pi;
  double constexpr eckert_5_y_max = std::numbers::pi;
  point eckert_5_invert(double, double);

  double constexpr eckert_6_x_min = -2 * std::numbers::pi;
  double constexpr eckert_6_x_max = 2 * std::numbers::pi;
  double constexpr eckert_6_y_min = -std::numbers::pi;
  double constexpr eckert_6_y_max = std::numbers::pi;
  point eckert_6_invert(double, double);

  double constexpr collignon_x_min = -2 * std::sqrt(std::numbers::pi) * std::sqrt(2);
  double constexpr collignon_x_max = 2 * std::sqrt(std::numbers::pi) * std::sqrt(2);
  double constexpr collignon_y_min = std::sqrt(std::numbers::pi) * (1 - std::sqrt(2));
  double constexpr collignon_y_max = std::sqrt(std::numbers::pi);
  point collignon_invert(double, double);
  
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
