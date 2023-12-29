#include "rasterglyph.h"

namespace gle
{

/* ************************ RasterGlyph::RasterGlyph *********************** */

RasterGlyph::RasterGlyph (int x, int y, unsigned int width,
                          unsigned int height)
    : Glyph (width, height), m_x (x), m_y (y)
{
  //
}

/* ************************ RasterGlyph::RasterGlyph *********************** */

RasterGlyph::RasterGlyph (const RasterGlyph &glyph)
    : Glyph (glyph.m_width, m_height), m_x (glyph.m_x), m_y (glyph.m_y)
{
  //
}

/* ***************************** RasterGlyph::x **************************** */

int
RasterGlyph::x () const
{
  return m_x;
}

/* ***************************** RasterGlyph::y **************************** */

int
RasterGlyph::y () const
{
  return m_y;
}

} // namespace gle
