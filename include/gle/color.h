#ifndef COLOR_H
#define COLOR_H

#include <glm/vec4.hpp>

enum class ColorType
{
  luminance,
  luminance_alpha,
  rgb,
  rgb_alpha
};

unsigned int
color_size (ColorType ct)
{
  switch (ct)
    {

    case ColorType::luminance:
      return 1;

    case ColorType::luminance_alpha:
      return 2;

    case ColorType::rgb:
      return 3;

    case ColorType::rgb_alpha:
      return 4;

    default:
      return 0;
    }
}

#endif // COLOR_H
