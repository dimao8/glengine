#ifndef RASTERGLYPH_H
#define RASTERGLYPH_H

#include "glyph.h"

namespace gle
{

class RasterGlyph : public Glyph
{

protected:
  int m_x;
  int m_y;

public:
  RasterGlyph () = delete;
  RasterGlyph (const RasterGlyph & glyph);
  RasterGlyph (int x, int y, unsigned int width, unsigned int height);
  int x () const;
  int y () const;
};

} // namespace gle

#endif // RASTERGLYPH_H
