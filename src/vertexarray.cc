#include <gle/attribute.h>
#include <gle/buffer.h>
#include <gle/logger.h>
#include <gle/vertexarray.h>

#include "opengl.h"
#include "translate.h"

namespace gle
{

/* ************************ VertexArray::VertexArray *********************** */

VertexArray::VertexArray ()
{
  GLenum result;
  glGenVertexArrays (1, &m_handle);

  // Check for vertex array valid
  if (m_handle == 0)
    {
      result = glGetError ();
      LOG_PRINT (SeverityLevel::error,
                 "Create vertex buffer cause GL error: ``%s\'\'\n",
                 message_gl (result));
      return;
    }

  glBindVertexArray (m_handle);
}

/* *********************** VertexArray::~VertexArray *********************** */

VertexArray::~VertexArray ()
{
  if (m_handle != 0)
    glDeleteVertexArrays (1, &m_handle);
}

/* ************************ VertexArray::add_buffer ************************ */

void
VertexArray::add_buffer (Buffer *buffer)
{
  GLsizei stride = 0;
  unsigned int offs = 0;

  if (buffer != nullptr)
    {
      if (!buffer->is_empty () && buffer->get_attribute_count () != 0)
        {
          m_buffers.push_back (buffer);
          buffer->enable ();
          for (size_t n = 0; n < buffer->get_attribute_count (); n++)
            stride += buffer->get_attribute (n)->get_size();
          for (size_t n = 0; n < buffer->get_attribute_count (); n++)
            {
              glVertexAttribPointer (
                  buffer->get_attribute (n)->get_number (),
                  buffer->get_attribute (n)->get_elements (),
                  buffer->get_attribute (n)->get_gl_type (),
                  buffer->get_attribute (n)->is_normalized () ? GL_TRUE : GL_FALSE,
                  stride, reinterpret_cast<void*>(offs));
              offs += buffer->get_attribute (n)->get_size();
            }
        }
    }
}

}