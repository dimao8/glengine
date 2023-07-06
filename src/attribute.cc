#include <gle/attribute.h>

#include "opengl.h"

namespace gle
{

/* ************************** Attribute::Attribute ************************* */

Attribute::Attribute (AttributeType type, int number, bool normalized,
                      const std::string &name)
    : m_type (type), m_number (number), m_name (name), m_size (0),
      m_elements (0), m_gl_type (GL_FLOAT), m_normalized (normalized)
{
  switch (m_type)
    {
    case AttributeType::f:
      m_size = sizeof (GLfloat);
      m_elements = 1;
      m_gl_type = GL_FLOAT;
      break;

    case AttributeType::fv2:
      m_size = sizeof (GLfloat) * 2;
      m_elements = 2;
      m_gl_type = GL_FLOAT;
      break;

    case AttributeType::fv3:
      m_size = sizeof (GLfloat) * 3;
      m_elements = 3;
      m_gl_type = GL_FLOAT;
      break;

    case AttributeType::fv4:
      m_size = sizeof (GLfloat) * 4;
      m_elements = 4;
      m_gl_type = GL_FLOAT;
      break;

    case AttributeType::i:
      m_size = sizeof (GLint);
      m_elements = 1;
      m_gl_type = GL_INT;
      break;

    case AttributeType::iv2:
      m_size = sizeof (GLint) * 2;
      m_elements = 2;
      m_gl_type = GL_INT;
      break;

    case AttributeType::iv3:
      m_size = sizeof (GLint) * 3;
      m_elements = 3;
      m_gl_type = GL_INT;
      break;

    case AttributeType::iv4:
      m_size = sizeof (GLint) * 4;
      m_elements = 4;
      m_gl_type = GL_INT;
      break;

    case AttributeType::b:
      m_size = sizeof (GLboolean);
      m_elements = 1;
      m_gl_type = GL_BOOL;
      break;

    case AttributeType::bv2:
      m_size = sizeof (GLboolean) * 2;
      m_elements = 2;
      m_gl_type = GL_BOOL;
      break;

    case AttributeType::bv3:
      m_size = sizeof (GLboolean) * 3;
      m_elements = 3;
      m_gl_type = GL_BOOL;
      break;

    case AttributeType::bv4:
      m_size = sizeof (GLboolean) * 4;
      m_elements = 4;
      m_gl_type = GL_BOOL;
      break;
    }
}

/* ************************** Attribute::get_type ************************** */

AttributeType
Attribute::get_type () const
{
  return m_type;
}

/* ************************* Attribute::get_number ************************* */

int
Attribute::get_number () const
{
  return m_number;
}

/* ************************** Attribute::get_name ************************** */

const std::string &
Attribute::get_name () const
{
  return m_name;
}

/* ************************** Attribute::get_size ************************** */

size_t
Attribute::get_size () const
{
  return m_size;
}

/* ************************* Attribute::get_gl_type ************************ */

unsigned int
Attribute::get_gl_type () const
{
  return m_gl_type;
}

/* ************************ Attribute::is_normalized *********************** */

bool
Attribute::is_normalized () const
{
  return m_normalized;
}

}
