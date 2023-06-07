///
/// \file opengl.cc
/// \brief OpenGL common functions implementation
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

#include <GLFW/glfw3.h>
#include <gle/logger.h>

#define LOAD_GL_EXTENSION(x, y) \
  x = reinterpret_cast<y>(glfwGetProcAddress(#x)); \
  if (x == nullptr) \
    { \
      LOG_PRINT(SeverityLevel::warning, "Can not load ``%s\'\'\n", #x); \
      return false; \
    }

PFNGLGETSTRINGIPROC glGetStringi = nullptr;

PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = nullptr; 
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;

PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;

namespace gle
{

/* *************************** load_gl_extensions ************************** */

bool load_gl_extensions()
{
  LOAD_GL_EXTENSION(glGetStringi, PFNGLGETSTRINGIPROC);

  LOAD_GL_EXTENSION(glGenFramebuffers, PFNGLGENFRAMEBUFFERSPROC);
  LOAD_GL_EXTENSION(glDeleteFramebuffers, PFNGLDELETEFRAMEBUFFERSPROC);
  LOAD_GL_EXTENSION(glBindFramebuffer, PFNGLBINDFRAMEBUFFERPROC);
  LOAD_GL_EXTENSION(glFramebufferTexture2D, PFNGLFRAMEBUFFERTEXTURE2DPROC);

  LOAD_GL_EXTENSION(glCreateShader, PFNGLCREATESHADERPROC);
  LOAD_GL_EXTENSION(glDeleteShader, PFNGLDELETESHADERPROC);
  LOAD_GL_EXTENSION(glCompileShader, PFNGLCOMPILESHADERPROC);
  LOAD_GL_EXTENSION(glGetShaderiv, PFNGLGETSHADERIVPROC);
  LOAD_GL_EXTENSION(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
  LOAD_GL_EXTENSION(glShaderSource, PFNGLSHADERSOURCEPROC);

  return true;
}

}