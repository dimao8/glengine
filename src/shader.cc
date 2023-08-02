///
/// \file shader.cc
/// \brief Shader class implementation
/// \author Khruschev Dmitry aka DimaO
/// \version 0.1
///
/// \copyright Copyright (C) 2023 Khruschev Dmitry aka DimaO
///
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
// USA
//

#include "shader.h"
#include "logger.h"
#include "opengl.h"
#include "translate.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace gle
{

/* ***************************** Shader::Shader **************************** */

Shader::Shader (ShaderType type, const std::string &file_name)
    : m_handle (0), m_state (ShaderState::empty), m_type (type)
{
  GLenum result;

  switch (m_type)
    {

    case ShaderType::vertex:
      m_handle = glCreateShader (GL_VERTEX_SHADER);
      break;

    case ShaderType::fragment:
      m_handle = glCreateShader (GL_FRAGMENT_SHADER);
      break;

    case ShaderType::geometry:
      m_handle = glCreateShader (GL_GEOMETRY_SHADER);
      break;
    }

  // Check for shader valid
  if (m_handle == 0)
    {
      result = glGetError ();
      LOG_PRINT (SeverityLevel::error,
                 "Create shader cause GL error: ``%s\'\'\n",
                 message_gl (result));
      return;
    }

  // Get data from stream
  std::ifstream ifs (file_name, std::ios::binary);
  ifs.unsetf (std::ios::skipws);
  if (!ifs)
    {
      LOG_PRINT (SeverityLevel::error,
                 _ ("Can not load shader from file ``%s\'\'\n"),
                 file_name.c_str ());
      return;
    }
  else
    {
      LOG_PRINT (SeverityLevel::info,
                 _ ("Shader is loaded from file ``%s\'\'\n"),
                 file_name.c_str ());
    }

  size_t sz;

  ifs.seekg (0, std::ios::end);
  sz = ifs.tellg ();
  ifs.seekg (0, std::ios::beg);

  char *source = new char[sz + 2];

  ifs.read (source, sz);
  ifs.close ();

  source[sz] = 0;
  source[sz + 1] = 0;

  glShaderSource (m_handle, 1, &source, nullptr);

  delete[] source;

  m_state = ShaderState::source;

  compile ();
}

/* **************************** Shader::~Shader **************************** */

Shader::~Shader ()
{
  if (m_handle != 0)
    glDeleteShader (m_handle);
}

/* **************************** Shader::compile **************************** */

bool
Shader::compile ()
{
  GLint status;
  GLint len;
  char *log;

  if (m_state == ShaderState::empty)
    return false;

  glCompileShader (m_handle);
  glGetShaderiv (m_handle, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
    {
      m_state = ShaderState::source;
      glGetShaderiv (m_handle, GL_INFO_LOG_LENGTH, &len);
      log = new char[len];
      glGetShaderInfoLog (m_handle, len, nullptr, log);
      LOG_PRINT (SeverityLevel::error,
                 _ ("Can not compile shader. Compiler message:\n%s\n"), log);
      delete[] log;
    }
  else
    m_state = ShaderState::compiled;

  return m_state == ShaderState::compiled;
}

/* **************************** Shader::get_type *************************** */

ShaderType
Shader::get_type () const
{
  return m_type;
}

/* *************************** Shader::get_handle ************************** */

int
Shader::get_handle () const
{
  return m_handle;
}

/* **************************** Shader::is_empty *************************** */

bool
Shader::is_empty () const
{
  return m_state == ShaderState::empty;
}

/* ************************** Shader::is_compiled ************************** */

bool
Shader::is_compiled () const
{
  return m_state == ShaderState::compiled;
}

/* *************************** Shader::type_name *************************** */

const std::string
Shader::type_name () const
{
  return "Shader";
}

}
