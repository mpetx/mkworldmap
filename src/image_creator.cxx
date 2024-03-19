#include <iostream>
#include <cmath>
#include <memory>
#include <numbers>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "image_creator.hxx"

namespace mkworldmap
{
  image_creator::image_creator(earth_texture const & texture, projection const & proj, std::size_t width, double sl, bool south_up)
    : width { width },
      height { static_cast<std::size_t>(width * proj.height() / proj.width()) },
      standard_longitude { sl },
      texture { texture },
      south_up { south_up },
      proj { proj }
  {
  }

  color image_creator::color_at(double x, double y) const
  {
    if (south_up) {
      x = width - x - 1;
      y = height - y - 1;
    }
    double nx =  x * proj.width() / (width - 1) + proj.x_min;
    double ny = y * proj.height() / (height - 1) + proj.y_min;
    point p = proj.invert(nx, ny);
    if (std::isnan(p.x) || std::isnan(p.y))
      return color { 0xaa, 0xaa, 0xaa };
    p.x += standard_longitude;
    if (p.x < std::numbers::pi)
      p.x += 2 * std::numbers::pi;
    if (p.x >= std::numbers::pi)
      p.x -= 2 * std::numbers::pi;
    return texture.color_at(p.x, p.y);
  }

  void image_creator::save_image(std::string const & path) const
  {
    std::unique_ptr<char unsigned[]> buffer = std::make_unique<char unsigned[]>(width * height * 3);
    for (std::size_t y = 0; y < height; ++y) {
      for (std::size_t x = 0; x < width; ++x) {
	color c = color_at(x, y);
	std::size_t offset = y * 3 * width + x * 3;
	buffer[offset] = c.red;
	buffer[offset + 1] = c.green;
	buffer[offset + 2] = c.blue;
      }
    }
    stbi_write_jpg(path.c_str(), width, height, 3, buffer.get(), jpeg_quality);
  }
}
