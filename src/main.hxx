#ifndef MKWORLDMAP_MAIN_HXX_2024_03_18_KPCAMY4ZS8UA
#define MKWORLDMAP_MAIN_HXX_2024_03_18_KPCAMY4ZS8UA

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
    invalid
  };

  char const * get_command_line_option(char const * short_option, char const * long_option, int argc, char const * argv[]);
  int get_integral_command_line_option(char const * short_option, char const * long_option, int default_value, int argc, char const * argv[]);
  double get_floating_command_line_option(char const * short_option, char const * long_option, double default_value, int argc, char const * argv[]);
  bool get_boolean_command_line_option(char const * short_option, char const * long_option, bool default_value, int argc, char const * argv[]);
  
  char const * get_texture_file_path(int argc, char const * argv[]);
  projection_method get_projection_method(int argc, char const * argv[]);
  std::size_t get_output_image_width(int argc, char const * argv[]);
  double get_standard_longitude(int argc, char const * argv[]);
  char const * get_output_path(int argc, char const * argv[]);
  bool get_south_up(int argc, char const * argv[]);
  
  double get_standard_latitude(int argc, char const * argv[]);
  double get_max_latitude(int argc, char const * argv[]);

}

#endif
