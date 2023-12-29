#ifndef GLYPH_H
#define GLYPH_H

namespace gle
{

///
/// \brief Abstract font glyph
///
class Glyph
{

protected:
  unsigned int m_width;
  unsigned int m_height;

public:
  Glyph () = delete;
  Glyph (int width, int height);
  int width () const;
  int height () const;
};

};

#endif // GLYPH_H
