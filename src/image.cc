///
/// \file image.cc
/// \brief Image class implementation
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

#include "image.h"
#include "logger.h"
#include "translate.h"

#include <pngloader.h>
#include <tgaloader.h>

#include <fstream>

#define DEFAULT_IMAGE_WIDTH 512
#define DEFAULT_IMAGE_HEIGHT 512

namespace gle
{

const glm::uvec2 Image::default_image_size
    = glm::uvec2 (DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT);

/* ****************************** Image::Image ***************************** */

Image::Image (unsigned int width, unsigned int height, ColorType ct,
              const uint8_t *data)
    : Object ()
{
  if (data == nullptr)
    make_empty (width, height, ct);
  else
    {
      m_size.x = width;
      m_size.y = height;
      m_color_type = ct;
      m_data.assign (data, data + width * height * color_size (ct));
    }
}

/* ****************************** Image::Image ***************************** */

Image::Image (const std::string &file_name) : Object ()
{
  LOG_PRINT (SeverityLevel::info, _ ("Load image from ``%s\'\' file\n"),
             file_name.c_str ());

  std::ifstream ifs (file_name);
  if (!ifs)
    {
      LOG_PRINT (SeverityLevel::warning,
                 _ ("File ``%s\'\' not found or can not be read\n"),
                 file_name.c_str ());
      make_empty (default_image_size.x, default_image_size.y,
                  ColorType::rgb_alpha);
      return;
    }

  // Check for PNG
  const uint8_t png_signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
  bool is_png = true;
  std::vector<uint8_t> magic = { 0, 0, 0, 0, 0, 0, 0, 0 };
  ifs.read (reinterpret_cast<char *> (&(magic[0])), 8);
  uint8_t *data;
  png_header_t png_hdr;
  png_error_t png_result;
  unsigned int bpp;

  for (auto n = 0; n < 8; n++)
    {
      if (magic[n] != png_signature[n])
        {
          is_png = false;
          break;
        };
    }

  if (is_png)
    {
      LOG_PRINT (SeverityLevel::info,
                 _ ("Interpret image file ``%s\'\' as PNG\n"),
                 file_name.c_str ());
      png_result = LoadPNGFromFile (file_name.c_str (), &png_hdr, &data, true);
      if (png_result != PNG_ERROR_OK)
        {
          LOG_PRINT (SeverityLevel::warning,
                     _ ("Can not load PNG file. Reason: %i\n"), png_result);
          make_empty (default_image_size.x, default_image_size.y,
                      ColorType::rgb_alpha);
        }
      else
        {
          m_size.x = png_hdr.width;
          m_size.y = png_hdr.height;
          switch (png_hdr.color_type)
            {
            case 0:
              m_color_type = ColorType::luminance;
              break;

            case 2:
              m_color_type = ColorType::rgb;
              break;

            case 3:
              m_color_type = ColorType::rgb;
              break;

            case 4:
              m_color_type = ColorType::luminance_alpha;
              break;

            case 6:
              m_color_type = ColorType::rgb_alpha;
              break;

            default:
              break;
            }

          m_data.assign (
              data, data + color_size (m_color_type) * m_size.x * m_size.y);
        }
    }
  else // Check for TGA
    {
    }

  ifs.close ();
}

/* *************************** Image::make_empty *************************** */

void
Image::make_empty (unsigned int width, unsigned int height, ColorType ct)
{
  m_size.x = width;
  m_size.y = height;
  m_color_type = ct;
  m_data.assign (color_size (ct) * m_size.x * m_size.y, 255);
}

/* ****************************** Image::save ****************************** */

void
Image::save (const std::string &file_name)
{
  SaveTGA (m_size.x, m_size.y, color_size (m_color_type), m_data.data (),
           file_name.c_str ());
}

/* **************************** Image::type_name *************************** */

const std::string
Image::type_name () const
{
  return "Image";
}

}