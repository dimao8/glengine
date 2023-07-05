#include <gle/attribute.h>

#include "opengl.h"

namespace gle
{

/* ************************** Attribute::Attribute ************************* */

Attribute::Attribute (AttributeType type, int number, const std::string &name)
    : m_type (type), m_number (number), m_name (name)
{
}

/* ************************** Attribute::get_type ************************** */

AttributeType Attribute::get_type() const
{
  return m_type;
}

/* ************************* Attribute::get_number ************************* */

int Attribute::get_number() const
{
  return m_number;
}

/* ************************** Attribute::get_name ************************** */

const std::string & Attribute::get_name() const
{
  return m_name;
}

/* ************************** Attribute::get_size ************************** */

size_t Attribute::get_size() const
{
  switch (m_type)
  {
  case AttributeType::f:
    return sizeof(GLfloat);

  case AttributeType::fv2:
    return sizeof(GLfloat)*2;

  case AttributeType::fv3:
    return sizeof(GLfloat)*3;

  case AttributeType::fv4:
    return sizeof(GLfloat)*4;

  case AttributeType::i:
    return sizeof(GLint);

  case AttributeType::iv2:
    return sizeof(GLint)*2;

  case AttributeType::iv3:
    return sizeof(GLint)*3;

  case AttributeType::iv4:
    return sizeof(GLint)*4;

  case AttributeType::b:
    return sizeof(GLboolean);

  case AttributeType::bv2:
    return sizeof(GLboolean)*2;

  case AttributeType::bv3:
    return sizeof(GLboolean)*3;

  case AttributeType::bv4:
    return sizeof(GLboolean)*4;
  
  default:
    return 0;
  }
}

}
