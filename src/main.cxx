
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
    for (std::size_t i = 1; i < argc; ++i) {
      bool is_short_option = short_option && std::strcmp(argv[i], short_option) == 0;
      bool is_long_option = long_option && std::strcmp(argv[i], long_option) == 0;
      if (is_short_option || is_long_option) {
	return i == argc - 1 ? nullptr : argv[i + 1];
      }
    }
    return nullptr;
  }

  char const * get_texture_file_path(int argc, char const * argv[])
  {
    char const * default_texture_file_path = "./res/world.topo.bathy.200412.3x5400x2700.jpg";
    char const * option = get_command_line_option("-t", "--texture", argc, argv);
    return option ? option : default_texture_file_path;
  }

  projection_method get_projection_method(int argc, char const * argv[])
  {
    char const * method = get_command_line_option("-p", "--projection", argc, argv);
    if (!method)
      return projection_method::invalid;
    else if (std::strcmp(method, "equirectangular") == 0)
      return projection_method::equirectangular;
    else if (std::strcmp(method, "cylindrical-equal-area") == 0)
      return projection_method::cylindrical_equal_area;
    else
      return projection_method::invalid;
  }

  std::size_t get_output_image_width(int argc, char const * argv[])
  {
    std::size_t const default_width = 1024;
    char const * awidth = get_command_line_option("-w", "--width", argc, argv);
    if (!awidth)
      return default_width;
    int width = std::atoi(awidth);
    return width > 0 ? static_cast<std::size_t>(width) : default_width;
  }

  double get_standard_longitude(int argc, char const * argv[])
  {
    double const default_standard_longitude = 150.0;
    char const * asl = get_command_line_option("-s", "--standard-longitude", argc, argv);
    if (!asl)
      return default_standard_longitude;
    return std::atof(asl);
  }

  bool get_south_up(int argc, char const * argv[])
  {
    bool const default_south_up = false;
    char const * asu = get_command_line_option(nullptr, "--south-up", argc, argv);
    if (!asu)
      return default_south_up;
    return !(std::strcmp(asu, "F") == 0 || std::strcmp(asu, "f") == 0 || std::strcmp(asu, "no") == 0 || std::strcmp(asu, "No") == 0 || std::strcmp(asu, "0") == 0);
  }
  
  char const * get_output_path(int argc, char const * argv[])
  {
    char const * const default_output_path = "world-map.jpg";
    char const * path = get_command_line_option("-o", "--output", argc, argv);
    return path ? path : default_output_path;
  }

  double get_standard_latitude(int argc, char const * argv[])
  {
    double const default_standard_latitude = 0.0;
    char const * asl = get_command_line_option(nullptr, "--standard-latitude", argc, argv);
    if (!asl)
      return default_standard_latitude;
    return std::atof(asl);
  }

}

int main(int argc, char const * argv[])
{
  using namespace mkworldmap;
  mkworldmap::earth_texture texture { get_texture_file_path(argc, argv) };
  if (!texture) {
    std::cerr << "ERROR: failed to load a texture." << std::endl;
    return 1;
  }
  
  mkworldmap::projection_method proj_method = get_projection_method(argc, argv);
  if (proj_method == projection_method::invalid) {
    std::cerr << "ERROR: unknown projection method." << std::endl;
    return 1;
  }
  std::unique_ptr<mkworldmap::projection> proj { };
  switch (proj_method) {
  case projection_method::equirectangular: {
    proj = std::make_unique<mkworldmap::equirectangular_projection>();
  } break;
  case projection_method::cylindrical_equal_area: {
    double standard_latitude = get_standard_latitude(argc, argv);
    if (standard_latitude <= -90 || standard_latitude >= 90) {
      std::cerr << "ERROR: invalid standard latitude value.";
      return 1;
    }
    proj = std::make_unique<mkworldmap::cylindrical_equal_area_projection>(standard_latitude * std::numbers::pi / 180);
  } break;
  }
  
  std::size_t width = get_output_image_width(argc, argv);
  double standard_longitude = get_standard_longitude(argc, argv);
  if (standard_longitude < -180 || 180 < standard_longitude) {
    std::cerr << "ERROR: invalid standard longitude value.";
    return 1;
  }
  bool south_up = get_south_up(argc, argv);
  mkworldmap::image_creator creator { texture, *proj, width, standard_longitude * std::numbers::pi / 180, south_up };

  char const * output_path = get_output_path(argc, argv);
  creator.save_image(output_path);
  return 0;
}
