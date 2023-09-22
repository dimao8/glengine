///
/// \file image.h
/// \brief Image class header
/// \author Khruschev Dmitry aka DimaO
/// \version 0.1
///
/// \copyright Copyright (C) 2023 Khruschev Dmitry aka DimaO
///
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
// USA
//

#ifndef IMAGE_H
#define IMAGE_H

#include "object.h"
#include "color.h"

#include <cstdint>
#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace gle
{

/**
 * \brief The Image class
 *
 * The Image class contains image data and all image properties.
 */
class Image : public Object
{

private:
  static const glm::uvec2
      default_image_size; /// Static default image size constant

  glm::uvec2 m_size;      /// Size of the image
  ColorType m_color_type; /// Type of color of the image pixel
  std::vector<uint8_t>
      m_data; /// Raw image data in order of R, G, B, A or G, A

  void make_empty (unsigned int width, unsigned int height, ColorType ct);

public:
  /**
   * Create empty white image.
   *
   * \param [in] width -- Width of the image
   * \param [in] height -- Height of the image
   * \param [in] ct -- Type of the pixel color
   * \param [in] data -- Data of the image. If this pointer is nullptr, the
   * image will be white
   */
  Image (unsigned int width = default_image_size.x,
         unsigned int height = default_image_size.y,
         ColorType ct = ColorType::rgb_alpha, const uint8_t *data = nullptr);

  /**
   * Load image from the file
   *
   * \param [in] file_name -- Name of the image file
   *
   * \note Only PNG and TGA files are accepted
   */
  Image (const std::string &file_name);

  virtual ~Image() {}

  /**
   * Save image to the file
   *
   * \param [in] file_name -- Name of the TGA file
   */
  void save (const std::string &file_name);

  int width () const;
  int height () const;
  ColorType color_type () const;

  virtual const std::string type_name() const;
};

Logger& operator<<(Logger& logger, const Image& image);

}

#endif // IMAGE_H
