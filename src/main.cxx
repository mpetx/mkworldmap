
#include <iostream>
#include <cstring>
#include <memory>
#include <numbers>

#include "earth_texture.hxx"
#include "projection.hxx"
#include "image_creator.hxx"
#include "main.hxx"

namespace mkworldmap
{
  char const * get_command_line_option(char const * short_option, char const * long_option, int argc, char const * argv[])
  {
    for (std::size_t i = 1; i < argc - 1; ++i) {
      bool is_short_option = short_option && std::strcmp(argv[i], short_option) == 0;
      bool is_long_option = long_option && std::strcmp(argv[i], long_option) == 0;
      if (is_short_option || is_long_option) {
	return argv[i + 1];
      }
    }
    return nullptr;
  }

  int get_integral_command_line_option(char const * short_option, char const * long_option, int default_value, int argc, char const * argv[])
  {
    char const * option_value = get_command_line_option(short_option, long_option, argc, argv);
    return option_value ? std::atoi(option_value) : default_value;
  }

  double get_floating_command_line_option(char const * short_option, char const * long_option, double default_value, int argc, char const * argv[])
  {
    char const * option_value = get_command_line_option(short_option, long_option, argc, argv);
    return option_value ? std::atof(option_value) : default_value;
  }

  bool get_boolean_command_line_option(char const * short_option, char const * long_option, bool default_value, int argc, char const * argv[])
  {
    for (std::size_t i = 1; i < argc; ++i) {
      bool is_short_option = short_option && std::strcmp(argv[i], short_option) == 0;
      bool is_long_option = long_option && std::strcmp(argv[i], long_option) == 0;
      if (is_short_option || is_long_option) {
	return true;
      }
    }
    return false;
  }
  
  char const * get_texture_file_path(int argc, char const * argv[])
  {
    char const * option_value = get_command_line_option("-t", "--texture", argc, argv);
    return option_value ? option_value : "./res/world.topo.bathy.200412.3x5400x2700.jpg";
  }

  projection_method get_projection_method(int argc, char const * argv[])
  {
    char const * method = get_command_line_option("-p", "--projection", argc, argv);
    return !method ? projection_method::invalid
      : std::strcmp(method, "equirectangular") == 0 ? projection_method::equirectangular
      : std::strcmp(method, "cylindrical-equal-area") == 0 ? projection_method::cylindrical_equal_area
      : std::strcmp(method, "mercator") == 0 ? projection_method::mercator
      : std::strcmp(method, "miller") == 0 ? projection_method::miller
      : std::strcmp(method, "central-cylindrical") == 0 ? projection_method::central_cylindrical
      : std::strcmp(method, "sinusoidal") == 0 ? projection_method::sinusoidal
      : std::strcmp(method, "mollweide") == 0 ? projection_method::mollweide
      : std::strcmp(method, "azimuthal-equidistant") == 0 ? projection_method::azimuthal_equidistant
      : std::strcmp(method, "aitoff") == 0 ? projection_method::aitoff
      : std::strcmp(method, "orthographic") == 0 ? projection_method::orthographic
      : std::strcmp(method, "orthographic-aitoff") == 0 ? projection_method::orthographic_aitoff
      : projection_method::invalid;
  }

  std::size_t get_output_image_width(int argc, char const * argv[])
  {
    return get_integral_command_line_option("-w", "--width", 768, argc, argv);
  }

  double get_standard_longitude(int argc, char const * argv[])
  {
    return get_floating_command_line_option("-s", "--standard-longitude", 150.0, argc, argv);
  }

  bool get_south_up(int argc, char const * argv[])
  {
    return get_boolean_command_line_option(nullptr, "--south-up", false, argc, argv);
  }
  
  char const * get_output_path(int argc, char const * argv[])
  {
    char const * option_value = get_command_line_option("-o", "--output", argc, argv);
    return option_value ? option_value : "world-map.jpg";
  }

  double get_standard_latitude(int argc, char const * argv[])
  {
    return get_floating_command_line_option(nullptr, "--standard-latitude", 0.0, argc, argv);
  }

  double get_max_latitude(int argc, char const * argv[])
  {
    return get_floating_command_line_option(nullptr, "--max-latitude", 80.0, argc, argv);
  }

}

int main(int argc, char const * argv[])
{
  using namespace mkworldmap;
  earth_texture texture { get_texture_file_path(argc, argv) };
  if (!texture) {
    std::cerr << "ERROR: failed to load a texture." << std::endl;
    return 1;
  }
  
  projection_method proj_method = get_projection_method(argc, argv);
  if (proj_method == projection_method::invalid) {
    std::cerr << "ERROR: unknown projection method." << std::endl;
    return 1;
  }
  std::unique_ptr<projection> proj { };
  switch (proj_method) {
  case projection_method::equirectangular: {
    proj = std::make_unique<equirectangular_projection>();
  } break;
  case projection_method::cylindrical_equal_area: {
    double standard_latitude = get_standard_latitude(argc, argv);
    proj = std::make_unique<cylindrical_equal_area_projection>(standard_latitude * std::numbers::pi / 180);
  } break;
  case projection_method::mercator: {
    double max_latitude = get_max_latitude(argc, argv);
    proj = std::make_unique<mercator_projection>(max_latitude * std::numbers::pi / 180);
  } break;
  case projection_method::miller: {
    proj = std::make_unique<miller_projection>();
  } break;
  case projection_method::central_cylindrical: {
    double max_latitude = get_max_latitude(argc, argv);
    proj = std::make_unique<central_cylindrical_projection>(max_latitude * std::numbers::pi / 180);
  } break;
  case projection_method::sinusoidal: {
    proj = std::make_unique<sinusoidal_projection>();
  } break;
  case projection_method::mollweide: {
    proj = std::make_unique<mollweide_projection>();
  } break;
  case projection_method::azimuthal_equidistant: {
    proj = std::make_unique<azimuthal_equidistant_projection>();
  } break;
  case projection_method::aitoff: {
    proj = std::make_unique<aitoff_projection>();
  } break;
  case projection_method::orthographic: {
    proj = std::make_unique<orthographic_projection>();
  } break;
  case projection_method::orthographic_aitoff: {
    proj = std::make_unique<orthographic_aitoff_projection>();
  } break;
  }
  
  std::size_t width = get_output_image_width(argc, argv);
  double standard_longitude = get_standard_longitude(argc, argv);
  bool south_up = get_south_up(argc, argv);
  image_creator creator { texture, *proj, width, standard_longitude * std::numbers::pi / 180, south_up };

  char const * output_path = get_output_path(argc, argv);
  creator.save_image(output_path);
  return 0;
}
