#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <gle/color.h>
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

  /**
   * Save image to the file
   *
   * \param [in] file_name -- Name of the TGA file
   */
  void save (const std::string &file_name);
};

}

#endif // IMAGE_H
