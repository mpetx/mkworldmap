#ifndef MKWORLDMAP_EARTH_TEXTURE_HXX_2024_03_18_TU2ERVFVMC9G
#define MKWORLDMAP_EARTH_TEXTURE_HXX_2024_03_18_TU2ERVFVMC9G

#include <string>
#include <memory>
#include <numbers>

#include "util.hxx"

namespace mkworldmap
{
  class earth_texture
  {
    int width;
    int height;
    std::shared_ptr<char unsigned[]> buffer;

    color color_at_grid(std::size_t, std::size_t) const;

    static double constexpr longitude_min = -std::numbers::pi;
    static double constexpr longitude_max = std::numbers::pi;
    static double constexpr latitude_min = -std::numbers::pi * 0.5;
    static double constexpr latitude_max = std::numbers::pi * 0.5;

  public:

    earth_texture() = default;
    earth_texture(earth_texture const &) = default;
    earth_texture(earth_texture &&) = default;
    earth_texture & operator=(earth_texture const &) = default;
    earth_texture & operator=(earth_texture &&) = default;
    earth_texture(std::string const &);

    color color_at(double, double) const;
    
    explicit operator bool() const;
  };
}

#endif
