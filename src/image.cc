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
#include "utils.h"

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

Image::Image (unsigned int width, unsigned int height, ColorType ct,
              const Color &fill)
    : m_size (width, height), m_color_type (ct)
{
  m_data.resize (m_size.x * m_size.y * Color::color_size (m_color_type));
  std::array<uint8_t, 4> cl = { 0, 0, 0, 0 };

  switch (m_color_type)
    {
    case ColorType::luminance:
      cl[0] = std::clamp<uint8_t> (
          (static_cast<float> (fill.color_ptr ()[0]) * 0.299f
           + static_cast<float> (fill.color_ptr ()[1]) * 0.587f
           + static_cast<float> (fill.color_ptr ()[2]) * 0.114f)
              * 255.0f,
          0, 255);
      logger << SeverityLevel::info << "{" << static_cast<unsigned int> (cl[0])
             << ", " << static_cast<unsigned int> (cl[1]) << ", "
             << static_cast<unsigned int> (cl[2]) << ", "
             << static_cast<unsigned int> (cl[3]) << "}" << std::endl;
      for (auto i = 0; i < m_size.x * m_size.y; i++)
        m_data[i] = static_cast<unsigned int> (cl[0]);
      break;

    case ColorType::luminance_alpha:
      cl[0] = std::clamp<uint8_t> (
          (static_cast<float> (fill.color_ptr ()[0]) * 0.299f
           + static_cast<float> (fill.color_ptr ()[1]) * 0.587f
           + static_cast<float> (fill.color_ptr ()[2]) * 0.114f)
              * 255.0f,
          0, 255);
      cl[1] = fill.color_ptr ()[3];
      logger << SeverityLevel::info << "{" << static_cast<unsigned int> (cl[0])
             << ", " << static_cast<unsigned int> (cl[1]) << ", "
             << static_cast<unsigned int> (cl[2]) << ", "
             << static_cast<unsigned int> (cl[3]) << "}" << std::endl;
      for (auto i = 0; i < m_size.x * m_size.y; i++)
        {
          m_data[i * 2] = static_cast<unsigned int> (cl[0]);
          m_data[i * 2 + 1] = static_cast<unsigned int> (cl[1]);
        }
      break;

    case ColorType::rgb:
      cl[0] = std::clamp<uint8_t> (fill.color_ptr ()[0] * 255.0f, 0, 255);
      cl[1] = std::clamp<uint8_t> (fill.color_ptr ()[1] * 255.0f, 0, 255);
      cl[2] = std::clamp<uint8_t> (fill.color_ptr ()[2] * 255.0f, 0, 255);
      logger << SeverityLevel::info << "{" << static_cast<unsigned int> (cl[0])
             << ", " << static_cast<unsigned int> (cl[1]) << ", "
             << static_cast<unsigned int> (cl[2]) << ", "
             << static_cast<unsigned int> (cl[3]) << "}" << std::endl;
      for (auto i = 0; i < m_size.x * m_size.y; i++)
        {
          m_data[i * 3] = static_cast<unsigned int> (cl[0]);
          m_data[i * 3 + 1] = static_cast<unsigned int> (cl[1]);
          m_data[i * 3 + 2] = static_cast<unsigned int> (cl[2]);
        }
      break;

    case ColorType::rgb_alpha:
      cl[0] = std::clamp<uint8_t> (fill.color_ptr ()[0] * 255.0f, 0, 255);
      cl[1] = std::clamp<uint8_t> (fill.color_ptr ()[1] * 255.0f, 0, 255);
      cl[2] = std::clamp<uint8_t> (fill.color_ptr ()[2] * 255.0f, 0, 255);
      cl[3] = std::clamp<uint8_t> (fill.color_ptr ()[3] * 255.0f, 0, 255);
      logger << SeverityLevel::info << "{" << static_cast<unsigned int> (cl[0])
             << ", " << static_cast<unsigned int> (cl[1]) << ", "
             << static_cast<unsigned int> (cl[2]) << ", "
             << static_cast<unsigned int> (cl[3]) << "}" << std::endl;
      for (auto i = 0; i < m_size.x * m_size.y; i++)
        {
          m_data[i * 4] = static_cast<unsigned int> (cl[0]);
          m_data[i * 4 + 1] = static_cast<unsigned int> (cl[1]);
          m_data[i * 4 + 2] = static_cast<unsigned int> (cl[2]);
          m_data[i * 4 + 3] = static_cast<unsigned int> (cl[3]);
        }
      break;
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

  ifs.read (reinterpret_cast<char *> (magic.data ()), 8);
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

/* ***************************** Image::bitblt ***************************** */

void
Image::bitblt (unsigned int dst_x, unsigned int dst_y, unsigned int src_width,
               unsigned int src_height, const uint8_t *src, ColorType ct,
               BlitOperation op)
{
  if (dst_x >= m_size.x || dst_y > m_size.y) // No intersection
    return;

  unsigned int src_x_tmp = 0;
  unsigned int src_y_tmp = 0;
  unsigned int dst_x_tmp = dst_x;
  unsigned int dst_y_tmp = dst_y;
  unsigned int width = std::min (m_size.x, dst_x + src_width) - dst_x;
  unsigned int height = std::min (m_size.y, dst_y + src_height) - dst_y;

  std::array<uint8_t, 4> src_pixel;
  size_t src_depth = Color::color_size (ct);
  std::array<uint8_t, 4> dst_pixel;
  size_t dst_depth = Color::color_size (m_color_type);
  std::array<uint8_t, 4> result_pixel;

  for (unsigned int j = 0; j < height; j++, src_y_tmp++, dst_y_tmp++)
    {
      src_x_tmp = 0;
      dst_x_tmp = dst_x;
      for (unsigned int i = 0; i < width; i++, src_x_tmp++, dst_x_tmp++)
        {
          switch (ct) // Source copy
            {
            case ColorType::luminance:
              src_pixel[0]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth];
              src_pixel[1]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth];
              src_pixel[2]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth];
              src_pixel[3] = 255;
              break;

            case ColorType::luminance_alpha:
              src_pixel[0]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth];
              src_pixel[1]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth];
              src_pixel[2]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth];
              src_pixel[3]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth + 1];
              break;

            case ColorType::rgb:
              src_pixel[0]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth];
              src_pixel[1]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth] + 1;
              src_pixel[2]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth] + 2;
              src_pixel[3] = 255;
              break;

            case ColorType::rgb_alpha:
              src_pixel[0]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth];
              src_pixel[1]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth] + 1;
              src_pixel[2]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth] + 2;
              src_pixel[3]
                  = src[(src_y_tmp * src_width + src_x_tmp) * src_depth] + 3;
              break;
            }

          switch (m_color_type) // Destination copy
            {
            case ColorType::luminance:
              dst_pixel[0]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth];
              dst_pixel[1]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth];
              dst_pixel[2]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth];
              dst_pixel[3] = 255;
              break;

            case ColorType::luminance_alpha:
              dst_pixel[0]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth];
              dst_pixel[1]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth];
              dst_pixel[2]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth];
              dst_pixel[3]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth + 1];
              break;

            case ColorType::rgb:
              dst_pixel[0]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth];
              dst_pixel[1]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth] + 1;
              dst_pixel[2]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth] + 2;
              dst_pixel[3] = 255;
              break;

            case ColorType::rgb_alpha:
              dst_pixel[0]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth];
              dst_pixel[1]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth] + 1;
              dst_pixel[2]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth] + 2;
              dst_pixel[3]
                  = m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth] + 3;
              break;
            }

          switch (op)
            {
            case BlitOperation::o_copy:
              result_pixel = src_pixel;
              if ((m_color_type != ColorType::luminance_alpha)
                  || (m_color_type != ColorType::rgb_alpha))
                result_pixel[3] = 255;
              break;

            case BlitOperation::o_sum:
              result_pixel[0] = sat_sum (src_pixel[0], dst_pixel[0]);
              result_pixel[1] = sat_sum (src_pixel[1], dst_pixel[1]);
              result_pixel[2] = sat_sum (src_pixel[2], dst_pixel[2]);
              result_pixel[3] = dst_pixel[3];
              break;

            case BlitOperation::o_and:
              result_pixel[0] = bitwise_and (src_pixel[0], dst_pixel[0]);
              result_pixel[1] = bitwise_and (src_pixel[1], dst_pixel[1]);
              result_pixel[2] = bitwise_and (src_pixel[2], dst_pixel[2]);
              result_pixel[3] = dst_pixel[3];
              break;

            case BlitOperation::o_or:
              result_pixel[0] = bitwise_or (src_pixel[0], dst_pixel[0]);
              result_pixel[1] = bitwise_or (src_pixel[1], dst_pixel[1]);
              result_pixel[2] = bitwise_or (src_pixel[2], dst_pixel[2]);
              result_pixel[3] = dst_pixel[3];
              break;
            }

          switch (m_color_type)
            {
            case ColorType::luminance:
              m_data[dst_y_tmp * m_size.x + dst_x_tmp] = result_pixel[0];
              break;

            case ColorType::luminance_alpha:
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth]
                  = result_pixel[0];
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth + 1]
                  = result_pixel[3];
              break;

            case ColorType::rgb:
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth]
                  = result_pixel[0];
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth + 1]
                  = result_pixel[1];
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth + 2]
                  = result_pixel[2];
              break;

            case ColorType::rgb_alpha:
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth]
                  = result_pixel[0];
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth + 1]
                  = result_pixel[1];
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth + 2]
                  = result_pixel[2];
              m_data[(dst_y_tmp * m_size.x + dst_x_tmp) * dst_depth + 3]
                  = result_pixel[3];
              break;
            }
        }
    }
}

/* ****************************** Image::width ***************************** */

unsigned int
Image::width () const
{
  return m_size.x;
}

/* ***************************** Image::height ***************************** */

unsigned int
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
  logger << "Image(" << image.width () << "x" << image.height () << "x"
         << static_cast<int> (Color::color_size (image.color_type ())) << ")"
         << std::endl;

  return logger;
}

}