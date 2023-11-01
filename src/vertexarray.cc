#include "vertexarray.h"
#include "attribute.h"
#include "logger.h"
#include "opengl.h"
#include "shaderprogram.h"
#include "translate.h"

namespace gle
{

/* ************************ VertexArray::VertexArray *********************** */

VertexArray::VertexArray (DrawingMode mode)
    : m_mode (mode), m_vertex_count (0), m_actual (false)
{
  GLenum result;
  glGenVertexArrays (1, &m_handle);

  // Check for vertex array valid
  if (m_handle == 0)
    {
      result = glGetError ();
      logger << SeverityLevel::error
             << _ ("Create vertex buffer cause GL error: ``")
             << message_gl (result) << "\'\'" << std::endl;
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
  for (auto it : m_attributes)
    delete it;
}

/* ************************ VertexArray::add_buffer ************************ */

void
VertexArray::add_buffer (Buffer *buffer, Attribute *attribute)
{
  GLsizei stride = 0;
  unsigned int offs = 0;
  bool exist = false;

  if (buffer == nullptr)
    {
      logger << SeverityLevel::warning << _ ("Try to add null buffer object")
             << std::endl;
      return;
    }

  Buffer *buf = nullptr;

  for (auto it : m_buffers)
    {
      if (buffer == it)
        buf = it;
    }
  if (buf == nullptr)
    {
      m_buffers.push_back (buffer);
      buf = buffer;
    }

  buf->add_attribute (attribute);

  m_actual = false;
}

/* ********************** VertexArray::remove_buffers ********************** */

void
VertexArray::remove_buffers ()
{
  m_buffers.clear ();
  m_actual = false;
}

/* *************************** VertexArray::draw *************************** */

void
VertexArray::draw (ShaderProgram & program)
{
  GLint result;
  GLvoid *presult;

  program.enable ();
  enable ();

  glGetError ();
  glDrawArrays (m_gl_mode, 0, m_vertex_count);

  // logger << SeverityLevel::info << "ShaderProgram" << program.get_handle ()
  //        << ":" << std::endl;
  // glGetProgramiv (program.get_handle (), GL_ACTIVE_ATTRIBUTES, &result);
  // logger << "\tGL_ACTIVE_ATTRIBUTES: " << result << std::endl;
  // glGetProgramiv (program.get_handle (), GL_ACTIVE_UNIFORMS, &result);
  // logger << "\tGL_ACTIVE_UNIFORMS: " << result << std::endl;

  // for (auto i = 0; i < m_buffers[0]->attrib_count(); i++)
  //   {
  //     logger << SeverityLevel::info << "VertexAttribArray" << i
  //           << ":" << std::endl;
  //     glGetVertexAttribiv (i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &result);
  //     logger << "\tGL_VERTEX_ATTRIB_ARRAY_ENABLED: " << result << std::endl;
  //     glGetVertexAttribiv (i, GL_VERTEX_ATTRIB_ARRAY_SIZE, &result);
  //     logger << "\tGL_VERTEX_ATTRIB_ARRAY_SIZE: " << result << std::endl;
  //     glGetVertexAttribiv (i, GL_VERTEX_ATTRIB_ARRAY_TYPE, &result);
  //     logger << "\tGL_VERTEX_ATTRIB_ARRAY_TYPE: " << result << std::endl;
  //     glGetVertexAttribiv (i, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &result);
  //     logger << "\tGL_VERTEX_ATTRIB_ARRAY_NORMALIZED: " << result << std::endl;
  //     glGetVertexAttribiv (i, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &result);
  //     logger << "\tGL_VERTEX_ATTRIB_ARRAY_STRIDE: " << result << std::endl;
  //     glGetVertexAttribPointerv (i, GL_VERTEX_ATTRIB_ARRAY_POINTER, &presult);
  //     logger << "\tGL_VERTEX_ATTRIB_ARRAY_POINTER: "
  //           << reinterpret_cast<intptr_t> (presult) << std::endl;
  //     glGetVertexAttribiv (i, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &result);
  //     logger << "\tGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING: " << result << std::endl;
  //     glGetIntegerv (GL_ARRAY_BUFFER_BINDING, &result);
  //     logger << "\tGL_ARRAY_BUFFER_BINDING: " << result << std::endl;
  //   }
}

/* ************************** VertexArray::enable ************************** */

void
VertexArray::enable ()
{
  if (m_handle != 0)
    glBindVertexArray (m_handle);
}

/* ************************** VertexArray::update ************************** */

void
VertexArray::update ()
{
  GLsizei sz = 0;
  GLsizei offs = 0;

  m_vertex_count = 0;

  for (auto it : m_buffers)
    {
      sz = 0;
      offs = 0;
      it->enable ();
      it->update ();
      logger << SeverityLevel::warning << "Buffer content is "
             << (it->is_actual () ? "actual" : "not actual") << std::endl;
      for (int i = 0; i < it->attrib_count (); i++)
        sz += it->attribute (i)->get_size ();
      for (int i = 0; i < it->attrib_count (); i++)
        {
          glVertexAttribPointer (
              it->attribute (i)->get_index (),
              it->attribute (i)->get_element_count (),
              it->attribute (i)->get_gl_type (),
              it->attribute (i)->is_normalized () ? GL_TRUE : GL_FALSE, sz,
              reinterpret_cast<void *> (offs));
          glEnableVertexAttribArray (it->attribute (i)->get_index ());
          offs += it->attribute (i)->get_size ();
        }
    }

  sz = 0;

  for (auto i = 0; i < m_buffers[0]->attrib_count (); i++)
    sz += m_buffers[0]->attribute (i)->get_element_count ();

  m_vertex_count = m_buffers[0]->size () / sz;
  logger << SeverityLevel::info << "m_vertex_count: " << m_vertex_count
         << std::endl;

  m_actual = true;
}

/* ************************* VertexArray::is_actual ************************ */

bool
VertexArray::is_actual () const
{
  return m_actual;
}

}