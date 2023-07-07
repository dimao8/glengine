#include <gle/attribute.h>
#include <gle/buffer.h>
#include <gle/logger.h>
#include <gle/shaderprogram.h>
#include <gle/vertexarray.h>

#include "opengl.h"
#include "translate.h"

namespace gle
{

/* ************************ VertexArray::VertexArray *********************** */

VertexArray::VertexArray (DrawingMode mode) : m_mode (mode), m_vertex_count (0)
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

  switch (mode)
    {

    case DrawingMode::point:
      m_gl_mode = GL_POINTS;
      break;

    case DrawingMode::line:
      m_gl_mode = GL_LINES;
      break;

    case DrawingMode::line_strip:
      m_gl_mode = GL_LINE_STRIP;
      break;

    case DrawingMode::line_loop:
      m_gl_mode = GL_LINE_LOOP;
      break;

    case DrawingMode::triangle:
      m_gl_mode = GL_TRIANGLES;
      break;

    case DrawingMode::triangle_strip:
      m_gl_mode = GL_TRIANGLE_STRIP;
      break;

    case DrawingMode::triangle_fan:
      m_gl_mode = GL_TRIANGLE_FAN;
      break;
    }
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
          if (m_vertex_count < buffer->get_element_count())
            m_vertex_count = buffer->get_element_count();

          m_buffers.push_back (buffer);
          buffer->enable ();
          for (size_t n = 0; n < buffer->get_attribute_count (); n++)
            {
              stride += buffer->get_attribute (n)->get_size ();
            }
          for (size_t n = 0; n < buffer->get_attribute_count (); n++)
            {
              glVertexAttribPointer (
                  buffer->get_attribute (n)->get_number (),
                  buffer->get_attribute (n)->get_elements (),
                  buffer->get_attribute (n)->get_gl_type (),
                  buffer->get_attribute (n)->is_normalized () ? GL_TRUE
                                                              : GL_FALSE,
                  stride, reinterpret_cast<void *> (offs));
              offs += buffer->get_attribute (n)->get_size ();
            }
        }
    }
}

/* *************************** VertexArray::draw *************************** */

void
VertexArray::draw (ShaderProgram *program)
{
  if (program == nullptr)
    return;
  else
    program->enable ();

  enable ();

  LOG_PRINT(SeverityLevel::info, "glDrawArrays(%i, %i, %i)\n",
  static_cast<int>(m_gl_mode), static_cast<int>(0), static_cast<int>(m_vertex_count));

  glDrawArrays (m_gl_mode, 0, m_vertex_count);
}

/* ************************** VertexArray::enable ************************** */

void
VertexArray::enable ()
{
  if (m_handle != 0)
    glBindVertexArray (m_handle);
}

}