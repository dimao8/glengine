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

#include "opengl.h"

#include <gle/logger.h>
#include <gle/shader.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace gle
{

/* ***************************** Shader::Shader **************************** */

Shader::Shader (ShaderType type, const std::string &file_name)
    : m_handle (0), m_state (ShaderState::empty)
{
  switch (type)
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

  std::ifstream ifs (file_name, std::ios::binary);
  ifs.unsetf (std::ios::skipws);
  if (!ifs)
    {
      LOG_PRINT (SeverityLevel::error,
                 "Can not load shader from file ``%s\'\'\n",
                 file_name.c_str ());
      return;
    }
  else
    {
      LOG_PRINT (SeverityLevel::info, "Shader is loaded from file ``%s\'\'\n",
                 file_name.c_str ());
    }

  size_t sz;

  ifs.seekg(0, std::ios::end);
  sz = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  char* source = new char[sz + 2];

  ifs.read(source, sz);
  ifs.close ();

  source[sz] = 0;
  source[sz + 1] = 0;

  glShaderSource(m_handle, 1, &source, nullptr);

  delete[] source;

  m_state = ShaderState::source;

  compile ();
}

/* **************************** Shader::compile **************************** */

bool
Shader::compile ()
{
  GLint status;
  GLint len;
  char * log;

  if (m_state == ShaderState::empty)
    return false;

  glCompileShader(m_handle);
  glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
    {
      m_state = ShaderState::source;
      glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &len);
      log = new char[len];
      glGetShaderInfoLog(m_handle, len, nullptr, log);
      LOG_PRINT(SeverityLevel::error, "Can not compile shader. Reason:\n%s\n", log);
      delete[] log;
    }
  else
    m_state = ShaderState::compiled;

  return m_state == ShaderState::compiled;
}

}
