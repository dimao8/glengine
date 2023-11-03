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
#include "opengl.h"
#include "translate.h"

#include <algorithm>
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
              const uint8_t *data, bool vflip)
{
  if (data == nullptr)
    make_empty (width, height, ct);
  else
    {
      unsigned int bpp = Color::color_size (ct);

      m_size.x = width;
      m_size.y = height;
      m_color_type = ct;
      if (!vflip)
        m_data.assign (data, data + width * height * bpp);
      else
        {
          m_data.resize (height * width * bpp);
          for (auto i = 0; i < height; i++)
            {
              std::copy (data + (height - i - 1) * width * bpp,
                         data + (height - i) * width * bpp,
                         m_data.begin () + i * width * bpp);
            }
        }
    }
}

/* ****************************** Image::Image ***************************** */

Image::Image (const std::string &file_name)
{
  logger << SeverityLevel::info << _ ("Load image from ``")
         << file_name.c_str () << _ ("\'\' file") << std::endl;

  size_t sz;

  std::ifstream ifs (file_name);
  if (!ifs)
    {
      logger << SeverityLevel::warning << _ ("File ``") << file_name.c_str ()
             << _ ("\'\' not found or can not be read") << std::endl;
      make_empty (default_image_size.x, default_image_size.y,
                  ColorType::rgb_alpha);
      return;
    }

  // Check for PNG
  const std::array<uint8_t, 8> png_signature
      = { 137, 80, 78, 71, 13, 10, 26, 10 };
  bool is_png = true;
  std::array<uint8_t, 8> magic = { 0, 0, 0, 0, 0, 0, 0, 0 };

  ifs.seekg (0, std::ios_base::end);
  sz = ifs.tellg ();
  ifs.seekg (0, std::ios_base::beg);

  if (sz < 18)
    {
      // Have no PNG magic
      ifs.close ();
      logger << SeverityLevel::warning << _ ("File ``") << file_name.c_str ()
             << _ ("\'\' is smaller then smallest image") << std::endl;
      make_empty (default_image_size.x, default_image_size.y,
                  ColorType::rgb_alpha);
      return;
    }

  ifs.read (reinterpret_cast<char *> (magic.data()), 8);
  uint8_t *data;
  png_header_t png_hdr;
  png_error_t png_result;
  unsigned int bpp;

  if (magic == png_signature)
    {
      LOG_DEBUG (logger << SeverityLevel::info << _ ("Interpret image file ``")
                        << file_name.c_str () << _ ("\'\' as PNG file")
                        << std::endl);
      ifs.close ();
      png_result = LoadPNGFromFile (file_name.c_str (), &png_hdr, &data, true);
      if (png_result != PNG_ERROR_OK)
        {
          logger << SeverityLevel::warning
                 << _ ("Can not load PNG file. Reason: ") << png_result
                 << std::endl;
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
              data,
              data + Color::color_size (m_color_type) * m_size.x * m_size.y);
        }
    }
  else // Check for TGA
    {
      tga_header_t tga_hdr;
      tga_error_t tga_result;

      ifs.seekg (0, std::ios_base::beg);
      ifs.read (reinterpret_cast<char *> (&tga_hdr), sizeof (tga_header_t));
      ifs.close ();

      if (tga_hdr.image_type != TGA_IMAGE_COLOR_MAPPED
          && tga_hdr.image_type != TGA_IMAGE_TRUECOLOR
          && tga_hdr.image_type != TGA_IMAGE_GRAYSCALE
          && tga_hdr.image_type != TGA_IMAGE_RLE_COLOR_MAPPED
          && tga_hdr.image_type != TGA_IMAGE_RLE_TRUECOLOR
          && tga_hdr.image_type != TGA_IMAGE_RLE_GRAYSCALE)
        {
          logger << SeverityLevel::warning << _ ("File ``") << file_name
                 << _ ("\'\' probably not a valid TGA file ")
                 << static_cast<int> (tga_hdr.image_type) << std::endl;
          return;
        }

      LOG_DEBUG (logger << SeverityLevel::info << _ ("Interpret image file ``")
                        << file_name.c_str () << _ ("\'\' as TGA file")
                        << std::endl);
      tga_result = LoadTGAFromFile (file_name.c_str (), &tga_hdr, &data, true);
      if (tga_result != TGA_ERROR_OK)
        {
          logger << SeverityLevel::warning
                 << _ ("Can not load TGA file. Reason: ") << tga_result
                 << std::endl;
          make_empty (default_image_size.x, default_image_size.y,
                      ColorType::rgb_alpha);
        }
      else
        {
          m_size.x = tga_hdr.image_type_specification.width;
          m_size.y = tga_hdr.image_type_specification.height;
          switch (tga_hdr.image_type_specification.pixel_depth)
            {
            case 8:
              m_color_type = ColorType::luminance;
              break;

            case 16:
              m_color_type = ColorType::luminance_alpha;
              break;

            case 24:
              m_color_type = ColorType::rgb;
              break;

            case 32:
              m_color_type = ColorType::rgb_alpha;
              break;

            default:
              break;
            }

          m_data.assign (
              data,
              data + Color::color_size (m_color_type) * m_size.x * m_size.y);
        }
    }
}

/* *************************** Image::make_empty *************************** */

void
Image::make_empty (unsigned int width, unsigned int height, ColorType ct)
{
  m_size.x = width;
  m_size.y = height;
  m_color_type = ct;
  m_data.assign (Color::color_size (ct) * m_size.x * m_size.y, 255);
}

/* ****************************** Image::save ****************************** */

void
Image::save (const std::string &file_name)
{
  SaveTGA (m_size.x, m_size.y, Color::color_size (m_color_type),
           m_data.data (), file_name.c_str ());
}

/* ****************************** Image::width ***************************** */

int
Image::width () const
{
  return m_size.x;
}

/* ***************************** Image::height ***************************** */

int
Image::height () const
{
  return m_size.y;
}

/* *************************** Image::color_type *************************** */

ColorType
Image::color_type () const
{
  return m_color_type;
}

/* ***************************** Image::gl_type **************************** */

int
Image::gl_type () const
{
  switch (m_color_type)
    {

    case ColorType::luminance:
      return GL_RED;

    case ColorType::luminance_alpha:
      return GL_RG;

    case ColorType::rgb:
      return GL_RGB;

    case ColorType::rgb_alpha:
      return GL_RGBA;

    default:
      return 0;
    }
}

/* **************************** Image::data_ptr **************************** */

const uint8_t *
Image::data_ptr () const
{
  return m_data.data ();
}

/* ******************************* operator<< ****************************** */

Logger &
operator<< (Logger &logger, const Image &image)
{
  logger << "Image(" << image.width () << ")(" << image.width () << "x"
         << image.height () << "x"
         << static_cast<int> (Color::color_size (image.color_type ())) << ")"
         << std::endl;

  return logger;
}

}