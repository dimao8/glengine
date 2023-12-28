#include "rasterfont.h"
#include "logger.h"

#include <X11/Xlib.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <litejson.h>

#include <stdexcept>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

namespace gle
{

/* ************************* RasterFont::RasterFont ************************ */

RasterFont::RasterFont () : Font (), m_default_glyph (0, 0, 0, 0)
{
  LOG_DEBUG (logger << SeverityLevel::info
                    << "Extract default font: " << DEFAULT_FONT << std::endl);

  
}

/* ************************* RasterFont::RasterFont ************************ */

RasterFont::RasterFont (const std::string &file_name)
    : Font (), m_default_glyph (0, 0, 0, 0)
{
}

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

} // namespace gle
