#include <gle/attribute.h>

#include "opengl.h"

namespace gle
{

/* ************************** Attribute::Attribute ************************* */

Attribute::Attribute (AttributeType type, int index, bool normalized,
                      const std::string &name)
    : m_type (type), m_index (index), m_name (name), m_element_size (0),
      m_element_count (0), m_gl_type (GL_FLOAT), m_normalized (normalized)
{
  switch (m_type)
    {
    case AttributeType::f:
      m_element_size = sizeof (GLfloat);
      m_element_count = 1;
      m_gl_type = GL_FLOAT;
      break;

    case AttributeType::fv2:
      m_element_size = sizeof (GLfloat);
      m_element_count = 2;
      m_gl_type = GL_FLOAT;
      break;

    case AttributeType::fv3:
      m_element_size = sizeof (GLfloat);
      m_element_count = 3;
      m_gl_type = GL_FLOAT;
      break;

    case AttributeType::fv4:
      m_element_size = sizeof (GLfloat);
      m_element_count = 4;
      m_gl_type = GL_FLOAT;
      break;

    case AttributeType::i:
      m_element_size = sizeof (GLint);
      m_element_count = 1;
      m_gl_type = GL_INT;
      break;

    case AttributeType::iv2:
      m_element_size = sizeof (GLint);
      m_element_count = 2;
      m_gl_type = GL_INT;
      break;

    case AttributeType::iv3:
      m_element_size = sizeof (GLint);
      m_element_count = 3;
      m_gl_type = GL_INT;
      break;

    case AttributeType::iv4:
      m_element_size = sizeof (GLint);
      m_element_count = 4;
      m_gl_type = GL_INT;
      break;

    case AttributeType::b:
      m_element_size = sizeof (GLboolean);
      m_element_count = 1;
      m_gl_type = GL_BOOL;
      break;

    case AttributeType::bv2:
      m_element_size = sizeof (GLboolean);
      m_element_count = 2;
      m_gl_type = GL_BOOL;
      break;

    case AttributeType::bv3:
      m_element_size = sizeof (GLboolean);
      m_element_count = 3;
      m_gl_type = GL_BOOL;
      break;

    case AttributeType::bv4:
      m_element_size = sizeof (GLboolean);
      m_element_count = 4;
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

/* ************************** Attribute::get_index ************************* */

int
Attribute::get_index () const
{
  return m_index;
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
  return m_element_size*m_element_count;
}

/* ********************** Attribute::get_element_count ********************* */

size_t
Attribute::get_element_count () const
{
  return m_element_count;
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
