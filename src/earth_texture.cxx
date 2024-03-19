
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "earth_texture.hxx"
#include "util.hxx"

namespace mkworldmap
{
  
  earth_texture::earth_texture(std::string const & path)
  {
    int channels;
    char unsigned * raw_buffer = stbi_load(path.c_str(), &width, &height, &channels, 3);
    if (!raw_buffer)
      return;
    buffer = std::shared_ptr<char unsigned[]> { raw_buffer, stbi_image_free };
  }

  color earth_texture::color_at_grid(std::size_t x, std::size_t y) const
  {
    std::size_t offset = y * 3 * width + x * 3;
    return color {
      buffer[offset],
      buffer[offset + 1],
      buffer[offset + 2]
    };
  }

  color earth_texture::color_at(double x, double y) const
  {
    x = clamp(x, longitude_min, longitude_max);
    y = clamp(y, latitude_min, latitude_max);
    double nx = (x - longitude_min) * (width - 1) / (longitude_max - longitude_min);
    double ny = (y - latitude_min) * (height - 1) / (latitude_max - latitude_min);
    std::size_t ix = static_cast<std::size_t>(nx);
    std::size_t iy = static_cast<std::size_t>(ny);
    return color_at_grid(ix, iy);
  }
  
  earth_texture::operator bool() const
  {
    return static_cast<bool>(buffer);
  }
  
}
