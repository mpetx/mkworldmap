#ifndef MKWORLDMAP_IMAGE_CREATOR_HXX_2024_03_18_3PBXYX3HRRRY
#define MKWORLDMAP_IMAGE_CREATOR_HXX_2024_03_18_3PBXYX3HRRRY

#include <string>

#include "earth_texture.hxx"
#include "projection.hxx"

namespace mkworldmap
{
  class image_creator
  {

    std::size_t width;
    std::size_t height;
    double standard_longitude;
    earth_texture const & texture;
    projection const & proj;

    color color_at(double, double) const;

    static int constexpr jpeg_quality = 85;
    
  public:
    image_creator() = delete;
    image_creator(image_creator const &) = default;
    image_creator(image_creator &&) = default;
    image_creator & operator=(image_creator const &) = default;
    image_creator & operator=(image_creator &&) = default;
    image_creator(earth_texture const &, projection const &, std::size_t, double);

    void save_image(std::string const & path) const;
    
  };
}

#endif
