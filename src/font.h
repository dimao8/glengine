#ifndef FONT_H
#define FONT_H

#include "glyph.h"

#include <map>
#include <string>

namespace gle
{

///
/// \brief Font type
///
enum class FontType
{
  monospace,        /// Monospace font
  proportional      /// Proportional font
};

///
/// \brief Common font class
///
class Font
{

protected:
  std::string m_name;
  std::string m_author;
  std::string m_copyright;

  int m_x_height;
  int m_cap_height;
  int m_ascender_height;
  int m_descender_height;
  int m_width;
  int m_default_char;

  Glyph m_default_glyph;
  std::map<int, Glyph> m_glyphs;

public:
  Font ();
  virtual ~Font() {}

  virtual int width (int c) const;
  virtual int height (int c) const;

};

}

#endif // FONT_H
