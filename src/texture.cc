#include "texture.h"
#include "image.h"
#include "translate.h"

namespace gle
{

const uint8_t Texture::default_texture[]
    = { 255, 0, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 0, 255, 255 };

/* *********************** Texture::generate_texture *********************** */

void
Texture::generate_texture (TextureFilter min_filter, TextureFilter mag_filter,
                           TextureWrap wrap_s, TextureWrap wrap_t)
{
  int result;

  glGenTextures (1, &m_handle);
  if (m_handle == 0)
    {
      result = glGetError ();
      logger << SeverityLevel::error << _ ("Create texture cause GL error: ``")
             << message_gl (result) << "\'\'" << std::endl;
      return;
    }

  enable ();

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                   static_cast<GLint> (min_filter));
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                   static_cast<GLint> (mag_filter));

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                   static_cast<GLint> (wrap_s));
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                   static_cast<GLint> (wrap_t));

  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, m_image->width (),
                m_image->height (), 0, m_image->gl_type (), GL_UNSIGNED_BYTE,
                reinterpret_cast<const GLvoid *> (m_image->data_ptr ()));
}

/* **************************** Texture::Texture *************************** */

Texture::Texture ()
    : m_image (new Image (2, 2, ColorType::rgb_alpha, default_texture))
{
  generate_texture (TextureFilter::nearest, TextureFilter::nearest,
                    TextureWrap::clamp_to_edge, TextureWrap::clamp_to_edge);
}

/* **************************** Texture::Texture *************************** */

Texture::Texture (int width, int height, ColorType color_type)
{
  int result;

  glGenTextures (1, &m_handle);
  if (m_handle == 0)
    {
      result = glGetError ();
      logger << SeverityLevel::error << _ ("Create texture cause GL error: ``")
             << message_gl (result) << "\'\'" << std::endl;
      return;
    }

  enable ();

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D (GL_TEXTURE_2D, 0, Color::color_type_gl (color_type), width,
                height, 0, Color::color_type_gl (color_type), GL_UNSIGNED_BYTE,
                nullptr);
}

/* **************************** Texture::Texture *************************** */

Texture::Texture (const std::string &file_name)
    : m_image (new Image (file_name))
{
  generate_texture (TextureFilter::nearest, TextureFilter::nearest,
                    TextureWrap::clamp_to_edge, TextureWrap::clamp_to_edge);
}

/* *************************** Texture::~Texture *************************** */

Texture::~Texture ()
{
  GLint result;

  glGetIntegerv (GL_TEXTURE_BINDING_2D, &result);
  if (result == m_handle)
    disable ();
  glDeleteTextures (1, &m_handle);
}

/* **************************** Texture::enable **************************** */

void
Texture::enable (int index)
{
  glActiveTexture (GL_TEXTURE0 + index);
  glBindTexture (GL_TEXTURE_2D, m_handle);
}

/* ************************* Texture::set_filtering ************************ */

void
Texture::set_filtering (TextureFilter min_filter, TextureFilter mag_filter)
{
  enable ();
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                   static_cast<GLint> (min_filter));
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                   static_cast<GLint> (mag_filter));
}

/* **************************** Texture::handle **************************** */

GLuint
Texture::handle () const
{
  return m_handle;
}

/* **************************** Texture::disable *************************** */

void
Texture::disable ()
{
  glBindTexture (GL_TEXTURE_2D, 0);
}

}