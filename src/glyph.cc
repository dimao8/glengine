#include "glyph.h"

namespace gle
{

/* ****************************** Glyph::Glyph ***************************** */

Glyph::Glyph (int width, int height) : m_width (width), m_height (height)
{
  //
}

/* ****************************** Glyph::width ***************************** */

int
Glyph::width () const
{
  return m_width;
}

/* ***************************** Glyph::height ***************************** */

int
Glyph::height () const
{
  return m_height;
}

};
