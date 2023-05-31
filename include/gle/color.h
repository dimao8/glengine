#ifndef COLOR_H
#define COLOR_H

#include <glm/vec4.hpp>

namespace gle
{

enum class ColorType
{
  luminance,
  luminance_alpha,
  rgb,
  rgb_alpha
};

/**
 * Get size of pixel with ColorType
 *
 * \param [in] ct -- Color type
 * \return Return size in bytes of corresponding pixel
 */
unsigned int color_size (ColorType ct);

}

#endif // COLOR_H
