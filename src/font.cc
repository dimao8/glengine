#include "font.h"

namespace gle
{

/* ******************************* Font::Font ****************************** */

Font::Font () :
  m_default_glyph (0, 0)
{
  //
}

/* ****************************** Font::width ****************************** */

int
Font::width (int c) const
{
  auto it = m_glyphs.find (c);
  if (it == m_glyphs.end ())
    return m_default_glyph.width ();
  else
    return it->second.width ();
}

/* ****************************** Font::height ***************************** */

int
Font::height (int c) const
{
  auto it = m_glyphs.find (c);
  if (it == m_glyphs.end ())
    return m_default_glyph.height ();
  else
    return it->second.height ();
}

} // namespace gle
