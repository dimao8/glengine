#include "buffer.h"
#include "attribute.h"
#include "logger.h"
#include "opengl.h"
#include "translate.h"

namespace gle
{

unsigned int
Buffer::buffer_type_to_glenum (BufferAccess access,
                               BufferOptimization optimization)
{
  if (access == BufferAccess::draw)
    {
      if (optimization == BufferOptimization::stat)
        return GL_STATIC_DRAW;
      else if (optimization == BufferOptimization::dyn)
        return GL_DYNAMIC_DRAW;
      else
        return GL_STREAM_DRAW;
    }
  else if (access == BufferAccess::read)
    {
      if (optimization == BufferOptimization::stat)
        return GL_STATIC_READ;
      else if (optimization == BufferOptimization::dyn)
        return GL_DYNAMIC_READ;
      else
        return GL_STREAM_READ;
    }
  else
    {
      if (optimization == BufferOptimization::stat)
        return GL_STATIC_COPY;
      else if (optimization == BufferOptimization::dyn)
        return GL_DYNAMIC_COPY;
      else
        return GL_STREAM_COPY;
    }
}

/* ***************************** Buffer::Buffer **************************** */

Buffer::Buffer (BufferAccess access, BufferOptimization optimization,
                size_t data_size, const void *data)
    : m_handle (0), m_access (BufferAccess::draw),
      m_optimization (BufferOptimization::stat), m_actual (false)
{
  GLenum usage;
  GLenum result;

  glGenBuffers (1, &m_handle);

  // Check for buffer valid
  if (m_handle == 0)
    {
      result = glGetError ();
      logger << SeverityLevel::error << _ ("Create buffer cause GL error: ``")
             << message_gl (result) << "\'\'" << std::endl;
      return;
    }

  glBindBuffer (GL_ARRAY_BUFFER, m_handle);

  if (data_size != 0 && data != nullptr)
    append_data (access, optimization, data_size, data);
}

/* ***************************** Buffer::clear ***************************** */

void
Buffer::clear ()
{
  m_data.clear ();
  m_attributes.clear ();
  m_actual = false;
}

/* **************************** Buffer::set_data *************************** */

void
Buffer::append_data (BufferAccess access, BufferOptimization optimization,
                     size_t data_size, const void *data)
{
  m_data.insert (m_data.begin (), reinterpret_cast<const float *> (data),
                 reinterpret_cast<const float *> (data) + data_size);
  m_actual = false;
}

/* ************************* Buffer::add_attribute ************************* */

void
Buffer::add_attribute (Attribute *attribute)
{
  if (attribute == nullptr)
    {
      logger << SeverityLevel::warning << "Can not add attribute" << std::endl;
      return;
    }

  m_attributes.push_back (attribute);
}

/* ************************** Buffer::attrib_size ************************** */

size_t
Buffer::attrib_size () const
{
  return m_attributes.size ();
}

/* *************************** Buffer::attribute *************************** */

const Attribute *
Buffer::attribute (int i) const
{
  if (i >= m_attributes.size ())
    {
      logger << SeverityLevel::warning << "Attribute index out of bounds"
             << std::endl;
      return nullptr;
    }
  else
    return m_attributes[i];
}

/* ***************************** Buffer::update **************************** */

void
Buffer::update ()
{
  glBufferData (GL_ARRAY_BUFFER, m_data.size () * sizeof (float),
                m_data.data (),
                buffer_type_to_glenum (m_access, m_optimization));
  m_actual = true;
}

/* **************************** Buffer::~Buffer **************************** */

Buffer::~Buffer () { glDeleteBuffers (1, &m_handle); }

/* ***************************** Buffer::enable **************************** */

void
Buffer::enable ()
{
  if (m_handle != 0)
    glBindBuffer (GL_ARRAY_BUFFER, m_handle);
}

/* ****************************** Buffer::size ***************************** */

size_t
Buffer::size () const
{
  return m_data.size ();
}

/* **************************** Buffer::disable **************************** */

void
Buffer::disable ()
{
  glBindBuffer (GL_ARRAY_BUFFER, 0);
}

/* *************************** Buffer::is_actual *************************** */

bool
Buffer::is_actual () const
{
  return m_actual;
}

}
