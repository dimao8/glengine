#include "shaderprogram.h"
#include "logger.h"
#include "opengl.h"
#include "shader.h"
#include "translate.h"

namespace gle
{

/* ********************** ShaderProgram::ShaderProgram ********************* */

ShaderProgram::ShaderProgram (Shader *vertex, Shader *fragment,
                              Shader *geometry)
    : m_handle (0), m_vertex_shader (vertex), m_fragment_shader (fragment),
      m_geometry_shader (geometry), m_state (ShaderProgramState::empty)
{
  GLenum result;
  m_handle = glCreateProgram ();

  // Check for shader valid
  if (m_handle == 0)
    {
      result = glGetError ();
      logger << SeverityLevel::error
             << _ ("Create shader program cause GL error: ``")
             << message_gl (result) << "\'\'" << std::endl;
      return;
    }

  // Check for shaders
  if (m_vertex_shader != nullptr)
    {
      if (m_vertex_shader->get_type () != ShaderType::vertex
          || m_vertex_shader->is_empty ())
        {
          logger << SeverityLevel::error << _ ("Vertex shader is required")
                 << std::endl;
          m_vertex_shader = nullptr;
        }
      else
        {
          glAttachShader (
              m_handle, static_cast<GLuint> (m_vertex_shader->get_handle ()));
          logger << SeverityLevel::info
                 << _ ("Vertex shader is loaded and attached")
                 << std::endl;
        }
    }

  if (m_fragment_shader != nullptr)
    {
      if (m_fragment_shader->get_type () != ShaderType::fragment
          || m_fragment_shader->is_empty ())
        {
          logger << SeverityLevel::error << _ ("Fragment shader is required")
                 << std::endl;
          m_fragment_shader = nullptr;
        }
      else
        {
          glAttachShader (m_handle, static_cast<GLuint> (
                                        m_fragment_shader->get_handle ()));
          logger << SeverityLevel::info
                 << _ ("Fragment shader is loaded and attached")
                 << std::endl;
        }
    }

  if (m_geometry_shader != nullptr)
    {
      if (m_geometry_shader->get_type () != ShaderType::geometry
          || m_geometry_shader->is_empty ())
        {
          logger << SeverityLevel::warning << _ ("Geometry shader is required")
                 << std::endl;
          m_geometry_shader = nullptr;
        }
      else
        {
          glAttachShader (m_handle, static_cast<GLuint> (
                                        m_geometry_shader->get_handle ()));
          logger << SeverityLevel::info
                 << _ ("Geometry shader is loaded and attached")
                 << std::endl;
        }
    }

  if (m_vertex_shader != nullptr && m_fragment_shader != nullptr)
    m_state == ShaderProgramState::shaders;

  link ();
}

/* ************************** ShaderProgram::link ************************** */

bool
ShaderProgram::link ()
{
  GLint status;
  GLint len;
  char *log;

  if (m_state == ShaderProgramState::empty)
    return false;

  glLinkProgram (m_handle);
  glGetProgramiv (m_handle, GL_LINK_STATUS, &status);
  if (status == GL_FALSE)
    {
      m_state = ShaderProgramState::shaders;
      glGetProgramiv (m_handle, GL_INFO_LOG_LENGTH, &len);
      log = new char[len];
      glGetProgramInfoLog (m_handle, len, nullptr, log);
      logger << SeverityLevel::error
             << _ ("Can not link shader. Linker message:") << std::endl
             << log << std::endl;
      delete[] log;
    }
  else
    m_state = ShaderProgramState::linked;

  return m_state == ShaderProgramState::linked;
}

/* ************************* ShaderProgram::enable ************************* */

void
ShaderProgram::enable ()
{
  glUseProgram (m_handle);
}

/* ********************* ShaderProgram::~ShaderProgram ********************* */

ShaderProgram::~ShaderProgram ()
{
  if (m_vertex_shader)
    glDetachShader (m_handle, m_vertex_shader->get_handle ());
  if (m_fragment_shader)
    glDetachShader (m_handle, m_fragment_shader->get_handle ());
  if (m_geometry_shader)
    glDetachShader (m_handle, m_geometry_shader->get_handle ());

  if (m_handle != 0)
    glDeleteProgram (m_handle);
}

/* *********************** ShaderProgram::get_handle *********************** */

unsigned int
ShaderProgram::get_handle () const
{
  return m_handle;
}

/* ************************* ShaderProgram::disable ************************ */

void
ShaderProgram::disable ()
{
  glUseProgram (0);
}

/* ************************ ShaderProgram::is_linked *********************** */

bool
ShaderProgram::is_linked () const
{
  return m_state == ShaderProgramState::linked;
}

}
