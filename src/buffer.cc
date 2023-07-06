#include <gle/attribute.h>
#include <gle/buffer.h>
#include <gle/logger.h>

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
      m_optimization (BufferOptimization::stat), m_size (0)
{
  GLenum usage;
  GLenum result;

  glGenBuffers (1, &m_handle);

  // Check for buffer valid
  if (m_handle == 0)
    {
      result = glGetError ();
      LOG_PRINT (SeverityLevel::error,
                 "Create buffer cause GL error: ``%s\'\'\n",
                 message_gl (result));
      return;
    }

  glBindBuffer (GL_ARRAY_BUFFER, m_handle);

  if (data_size != 0)
    {
      glBufferData (GL_ARRAY_BUFFER, data_size, data,
                    buffer_type_to_glenum (m_access, m_optimization));
      m_size = data_size;
    }
}

/* **************************** Buffer::set_data *************************** */

void
Buffer::set_data (BufferAccess access, BufferOptimization optimization,
                  size_t data_size, const void *data)
{
  if (data == nullptr || data_size == 0)
    return;

  if (m_access == access && m_optimization == optimization && m_size)
    glBufferSubData (GL_ARRAY_BUFFER, 0, data_size, data);
  else
    {
      m_access = access;
      m_optimization = optimization;
      glBufferData (GL_ARRAY_BUFFER, data_size, data,
                    buffer_type_to_glenum (m_access, m_optimization));
    }
}

/* *********************** VertexArray::add_attribute ********************** */

void
Buffer::add_attribute (Attribute *attr)
{
  if (attr == nullptr)
    return;

  m_attributes.push_back (attr);
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

/* **************************** Buffer::is_empty *************************** */

bool
Buffer::is_empty () const
{
  return m_size == 0 || m_handle == 0;
}

/* ********************** Buffer::get_attribute_count ********************** */

size_t
Buffer::get_attribute_count () const
{
  return m_attributes.size ();
}

/* ************************* Buffer::get_attribute ************************* */

const Attribute *
Buffer::get_attribute (size_t n) const
{
  if (n >= m_attributes.size ())
    return nullptr;
  else
    return m_attributes[n];
}

/* **************************** Buffer::disable **************************** */

void
Buffer::disable ()
{
  glBindBuffer (GL_ARRAY_BUFFER, 0);
}

}
