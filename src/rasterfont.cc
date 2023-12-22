#include "rasterfont.h"
#include "logger.h"

#include <litejson.h>

#include <stdexcept>

namespace gle
{

/* ************************* RasterFont::RasterFont ************************ */

RasterFont::RasterFont (const std::string &file_name)
    : Font (), m_default_glyph (0, 0, 0, 0)
{
  litejson::JSONLoader json (file_name);

  if (json.is_bad ())
    {
      logger << SeverityLevel::error << "Can not load font from ``"
             << file_name << "\'\'" << std::endl;
      throw std::logic_error ("JSON loader error");
    }

  litejson::JSONValue *val = json.get_root ();
  
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
