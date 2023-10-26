#include "vertexarray.h"
#include "attribute.h"
#include "buffer.h"
#include "logger.h"
#include "opengl.h"
#include "shaderprogram.h"
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
      logger << SeverityLevel::error
             << _ ("Create vertex buffer cause GL error: ``")
             << message_gl (result) << _ ("\'\'") << std::endl;
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
          if (m_vertex_count < buffer->get_vertex_count ())
            m_vertex_count = buffer->get_vertex_count ();

          m_buffers.push_back (buffer);
          buffer->enable ();
          for (size_t n = 0; n < buffer->get_attribute_count (); n++)
            {
              stride += buffer->get_attribute (n)->get_size ();
            }
          for (size_t n = 0; n < buffer->get_attribute_count (); n++)
            {
              glVertexAttribPointer (
                  buffer->get_attribute (n)->get_index (),
                  buffer->get_attribute (n)->get_element_count (),
                  buffer->get_attribute (n)->get_gl_type (),
                  buffer->get_attribute (n)->is_normalized () ? GL_TRUE
                                                              : GL_FALSE,
                  stride, reinterpret_cast<void *> (offs));
              glEnableVertexAttribArray (
                  buffer->get_attribute (n)->get_index ());
              offs += buffer->get_attribute (n)->get_size ();
            }
        }
    }
}

/* ********************** VertexArray::remove_buffers ********************** */

void
VertexArray::remove_buffers ()
{
  m_buffers.clear ();
}

/* *************************** VertexArray::draw *************************** */

void
VertexArray::draw (ShaderProgram *program)
{
  if (program == nullptr)
    return;

  GLint param;

  glGetError ();
  program->enable ();
  logger << SeverityLevel::warning << _ ("OpenGL error: ")
         << message_gl (glGetError ()) << std::endl;
  glGetIntegerv (GL_CURRENT_PROGRAM, &param);
  logger << SeverityLevel::info << "glUseProgram(" << static_cast<int> (param)
         << ")" << std::endl;

  enable ();

  logger << SeverityLevel::info << "glDrawArrays("
         << static_cast<int> (m_gl_mode) << ", " << static_cast<int> (0)
         << ", " << static_cast<int> (m_vertex_count) << ")" << std::endl;

  glGetIntegerv (GL_ARRAY_BUFFER_BINDING, &param);
  logger << SeverityLevel::info
         << "GL_ARRAY_BUFFER_BINDING: " << static_cast<int> (param)
         << std::endl;
  glGetVertexAttribiv (0, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &param);
  logger << SeverityLevel::info
         << "GL_VERTEX_ATTRIB_ARRAY_ENABLED(0): " << static_cast<int> (param)
         << std::endl;
  glGetVertexAttribiv (1, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &param);
  logger << SeverityLevel::info
         << "GL_VERTEX_ATTRIB_ARRAY_ENABLED(1): " << static_cast<int> (param)
         << std::endl;

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