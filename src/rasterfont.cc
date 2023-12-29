#include "rasterfont.h"
#include "image.h"
#include "logger.h"

#include <X11/Xlib.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <litejson.h>

#include <stdexcept>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#define PIXELS_PER_INCH 96
#define CHAR_SIZE_PT 24
#define UNITS_TO_PIXELS(x) ((float)(x) / 26.6f)
#define PIXELS_TO_UNITS(x) ((float)(x) * 26.6f)
#define PT_TO_PIXELS(x) ((float)(x) * (float)(PIXELS_PER_INCH) / 72.0f)
#define PIXELS_TO_PT(x) ((float)(x) * 72.0f / (float)(PIXELS_PER_INCH))
#define UNITS_TO_PT(x) (PIXELS_TO_PT (UNITS_TO_PIXELS (x)))
#define PT_TO_UNITS(x) (PIXELS_TO_UNITS (PT_TO_PIXELS (x)))

namespace gle
{

/* ************************* RasterFont::RasterFont ************************ */

RasterFont::RasterFont () : Font (), m_default_glyph (0, 0, 0, 0)
{
  LOG_DEBUG (logger << SeverityLevel::info
                    << "Extract default font: " << DEFAULT_FONT << std::endl);

  m_atlas = new Image (256, 128, ColorType::luminance, Color (0, 0, 0, 1));

  FT_Library lib;
  FT_Error err = FT_Init_FreeType (&lib);

  FT_Face face;
  err = FT_New_Face (lib, DEFAULT_FONT, 0, &face);
  err = FT_Set_Char_Size (face, PT_TO_UNITS (CHAR_SIZE_PT), 0, PIXELS_PER_INCH,
                          0);

  FT_Vector pos = { 0, 0 };

  logger << SeverityLevel::warning << "Freetype Debug" << std::endl;
  for (int c = ' '; c <= '~'; c++)
    {
      FT_Set_Transform (face, nullptr, &pos);
      FT_Load_Char (face, c, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);

      m_atlas->bitblt (face->glyph->bitmap_left,
                       m_atlas->height () - face->glyph->bitmap_top - 3,
                       face->glyph->bitmap.width, face->glyph->bitmap.rows,
                       face->glyph->bitmap.buffer, ColorType::luminance);

      logger << c << ": {"
             << static_cast<int> (static_cast<float> (pos.x) / 26.6) << ", "
             << static_cast<int> (static_cast<float> (pos.y) / 26.6) << ", "
             << static_cast<int> (static_cast<float> (face->glyph->advance.x)
                                  / 26.6)
             << ", "
             << static_cast<int> (
                    static_cast<float> (face->glyph->metrics.vertAdvance)
                    / PIXELS_PER_INCH)
             << "}" << std::endl;
      m_glyphs.emplace (
          c,
          RasterGlyph (static_cast<int> (face->glyph->bitmap_left),
                       static_cast<int> (face->glyph->bitmap_top + 2),
                       static_cast<unsigned int> (face->glyph->bitmap.width),
                       static_cast<unsigned int> (face->glyph->bitmap.rows)));

      pos.x += face->glyph->advance.x;
      pos.y += face->glyph->advance.y;

      FT_Set_Transform (face, nullptr, &pos);
      FT_Load_Char (face, c + 1, FT_LOAD_RENDER);

      if (face->glyph->bitmap_left + face->glyph->bitmap.width
          > m_atlas->width ())
        {
          pos.x = 0;
          pos.y += face->glyph->metrics.vertAdvance;
        }
    }

  // Default character (U+FFFD)
  FT_Set_Transform (face, nullptr, &pos);
  FT_Load_Char (face, 0xFFFD, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);

  m_atlas->bitblt (face->glyph->bitmap_left,
                   m_atlas->height () - face->glyph->bitmap_top - 3,
                   face->glyph->bitmap.width, face->glyph->bitmap.rows,
                   face->glyph->bitmap.buffer, ColorType::luminance);

  logger << 0xFFFD << ": {"
         << static_cast<int> (static_cast<float> (pos.x) / 26.6) << ", "
         << static_cast<int> (static_cast<float> (pos.y) / 26.6) << ", "
         << static_cast<int> (static_cast<float> (face->glyph->advance.x)
                              / 26.6)
         << ", "
         << static_cast<int> (
                static_cast<float> (face->glyph->metrics.vertAdvance)
                / PIXELS_PER_INCH)
         << "}" << std::endl;
  m_glyphs.emplace (
      0xFFFD,
      RasterGlyph (static_cast<int> (face->glyph->bitmap_left),
                   static_cast<int> (face->glyph->bitmap_top + 2),
                   static_cast<unsigned int> (face->glyph->bitmap.width),
                   static_cast<unsigned int> (face->glyph->bitmap.rows)));

  FT_Done_Face (face);
  FT_Done_FreeType (lib);
}

/* ************************* RasterFont::RasterFont ************************ */

RasterFont::RasterFont (const std::string &file_name)
    : Font (), m_default_glyph (0, 0, 0, 0)
{
}

/* ************************ RasterFont::~RasterFont ************************ */

RasterFont::~RasterFont () { delete m_atlas; }

/* *************************** RasterFont::width *************************** */

int
RasterFont::width (int c) const
{
  auto it = m_glyphs.find (c);
  if (it == m_glyphs.end ())
    return m_default_glyph.width ();
  else
    return it->second.width ();
}

/* *************************** RasterFont::height ************************** */

int
RasterFont::height (int c) const
{
  auto it = m_glyphs.find (c);
  if (it == m_glyphs.end ())
    return m_default_glyph.width ();
  else
    return it->second.width ();
}

/* ***************************** RasterFont::x ***************************** */

int
RasterFont::x (int c) const
{
  auto it = m_glyphs.find (c);
  if (it == m_glyphs.end ())
    return m_default_glyph.x ();
  else
    return it->second.x ();
}

/* ***************************** RasterFont::y ***************************** */

int
RasterFont::y (int c) const
{
  auto it = m_glyphs.find (c);
  if (it == m_glyphs.end ())
    return m_default_glyph.y ();
  else
    return it->second.y ();
}

void
RasterFont::save_atlas (const std::string &file_name)
{
  m_atlas->save (file_name);
}

} // namespace gle
