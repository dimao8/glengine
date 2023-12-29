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

#include "color.h"
#include "logger.h"

#include <array>
#include <cstdint>
#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace gle
{

enum class BlitOperation
{
  o_copy,
  o_sum,
  o_diff,
  o_and,
  o_or
};

/**
 * \brief The Image class
 *
 * The Image class contains image data and all image properties.
 */
class Image
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
   * \param [in] hflip -- Horizontal flip
   */
  Image (unsigned int width = default_image_size.x,
         unsigned int height = default_image_size.y,
         ColorType ct = ColorType::rgb_alpha, const uint8_t *data = nullptr,
         bool vflip = false);

  /**
   * Create empty white image.
   *
   * \param [in] width -- Width of the image
   * \param [in] height -- Height of the image
   * \param [in] ct -- Type of the pixel color
   * \param [in] fill -- Fill color
   */
  Image (unsigned int width = default_image_size.x,
         unsigned int height = default_image_size.y,
         ColorType ct = ColorType::rgb_alpha,
         const Color &fill = { 0, 0, 0, 0 });

  /**
   * Load image from the file
   *
   * \param [in] file_name -- Name of the image file
   *
   * \note Only PNG and TGA files are accepted
   */
  Image (const std::string &file_name);

  virtual ~Image () {}

  /**
   * Save image to the file
   *
   * \param [in] file_name -- Name of the TGA file
   */
  void save (const std::string &file_name);

  ///
  /// \brief Bit blit operation
  /// \param [in] dst_x -- Destination X coordinate
  /// \param [in] dst_y -- Destination Y coordinate
  /// \param [in] src_width -- Source width
  /// \param [in] src_height -- Source height
  /// \param [in] src -- Source binary uncompressed data
  /// \param [in] ct -- Color type of the source image
  /// \param [in] op -- Blit operation
  ///
  /// Function bitblt makes blit operation with current image and raw source
  /// image. bitblt draw part or whole src image with size (src_width,
  /// src_height) to (dst_x, dst_y) point of the image. Coordinates of the
  /// images starts from upper left corner and rise to right and bottom.
  ///
  /// It is possible to draw source with destination border intersect. In that
  /// case source image will be cut. Drawing large source on the small
  /// destination will have the same result.
  ///
  /// Drawing keeps internal image format unchanged and translate source format
  /// to the image format with next rules:
  /// 1. If destination image format have larger depth than source, source will
  /// be extended.
  /// 2. If destination format have only one channel, destination translates to
  /// the grayscale and then draw implements.
  /// 3. Alpha channel will be kept, if it is exist in source and destination.
  /// 4. If destination has no alpha but source has, alpha channel discards.
  /// 5. If source has no alpha channel but destination has, source alpha
  /// channel assumed to be 255.
  ///
  /// There is some logic and arithmetic operations that can be implement
  /// during the draw process.
  /// 1. When o_copy is in use, simple copy from source to destination will be
  /// implemented.
  /// 2. When o_sum is in use, there will arithmetic sum of source and
  /// destination with saturation be implemented.
  /// 3. When o_diff is in use, there will be simple difference with zero
  /// saturation as a result.
  /// 4. When o_and is in use, there will be bitwise AND operation with source
  /// and destination.
  /// 5. When o_or is in use, there will be bitwise OR operation with source
  /// and destination.
  ///
  void bitblt (unsigned int dst_x, unsigned int dst_y, unsigned int src_width,
               unsigned int src_height, const uint8_t *src, ColorType ct,
               BlitOperation op = BlitOperation::o_copy);

  unsigned int width () const;
  unsigned int height () const;
  ColorType color_type () const;
  int gl_type () const;

  const uint8_t *data_ptr () const;

public:
  friend Logger &operator<< (Logger &logger, const Image &image);
};

}

#endif // IMAGE_H
