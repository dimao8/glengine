#ifndef RASTERFONT_H
#define RASTERFONT_H

#include "font.h"
#include "rasterglyph.h"

#include <string>

namespace gle
{

class Image;

///
/// \brief Raster font
///
class RasterFont : public Font
{

protected:
  Image * m_atlas; /// Texture atlas

  RasterGlyph m_default_glyph;
  std::map<int, RasterGlyph> m_glyphs;

public:
  RasterFont ();
  RasterFont (const RasterFont &) = delete;
  RasterFont (const std::string & file_name);
  virtual ~RasterFont ();

  virtual int width (int c) const override;
  virtual int height (int c) const override;
  virtual int x (int c) const;
  virtual int y (int c) const;

  void save_atlas(const std::string & file_name);

};

}

#endif // RASTERFONT_H
