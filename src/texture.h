#ifndef TEXTURE_H
#define TEXTURE_H

#include "opengl.h"
#include "color.h"

#include <memory>

namespace gle
{

class Image;

enum class TextureFilter
{
  nearest = GL_NEAREST,
  linear = GL_LINEAR
};

enum class TextureWrap
{
  clamp_to_edge = GL_CLAMP_TO_EDGE,
  clamp_to_border = GL_CLAMP_TO_BORDER,
  repeat = GL_REPEAT,
  mirrored_repeat = GL_MIRRORED_REPEAT
};

class Texture
{

private:

  GLuint m_handle;
  std::shared_ptr<Image> m_image;

  void generate_texture (TextureFilter min_filter, TextureFilter mag_filter,
    TextureWrap wrap_s, TextureWrap wrap_t);

public:

  Texture ();
  Texture (int width, int height, ColorType color_type);
  Texture (const std::string & file_name);
  virtual ~Texture ();
  void enable (int index = 0);
  void set_filtering (TextureFilter min_filter, TextureFilter mag_filter);

  GLuint handle () const;

private:

  static const uint8_t default_texture[];

public :

  static void disable ();

};

}

#endif // TEXTURE_H