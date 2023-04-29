#include <gle/image.h>
#include <gle/logger.h>
#include <pngloader.h>

#include <fstream>

#define DEFAULT_IMAGE_WIDTH 512
#define DEFAULT_IMAGE_HEIGHT 512

namespace gle
{

const glm::uvec2 Image::default_image_size
    = glm::uvec2 (DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT);

/* ****************************** Image::Image ***************************** */

Image::Image (unsigned int width, unsigned int height, ColorType ct)
{
  make_empty (width, height, ct);
}

/* ****************************** Image::Image ***************************** */

Image::Image (const std::string &file_name)
{
  LOG_PRINT (SeverityLevel::info, "Load image from ``%s\'\' file",
             file_name.c_str ());

  std::ifstream ifs (file_name);
  if (!ifs)
    {
      LOG_PRINT (SeverityLevel::warning,
                 "File ``%s\'\' not found or can not be read",
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
      LOG_PRINT (SeverityLevel::info, "Interpret image file ``%s\'\' as PNG",
                 file_name.c_str ());
      png_result = LoadPNGFromFile (file_name.c_str (), &png_hdr, &data, true);
      if (png_result != PNG_ERROR_OK)
        {
          LOG_PRINT (SeverityLevel::warning,
                     "Can not load PNG file. Reason: %i", png_result);
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
        }
    }
  else  // Check for TGA
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

}