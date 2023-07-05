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
#include "translate.h"

#include <GLFW/glfw3.h>
#include <gle/logger.h>

#define LOAD_GL_EXTENSION(x, y)                                               \
  x = reinterpret_cast<y> (glfwGetProcAddress (#x));                          \
  if (x == nullptr)                                                           \
    {                                                                         \
      LOG_PRINT (SeverityLevel::warning, "Can not load ``%s\'\'\n", #x);      \
      return false;                                                           \
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

PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLDETACHSHADERPROC glDetachShader = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;

const char *err_str_no_error = _("No error");
const char *err_str_invalid_enum = _("Invalid enumerator");
const char *err_str_invalid_value = _("Invalid value");
const char *err_str_invalid_operation = _("Invalid operation");
const char *err_str_stack_overflow = _("Stack overflow");
const char *err_str_stack_underflow = _("Stack underflow");
const char *err_str_out_of_memory = _("Out of memory");
const char *err_str_empty = "";

namespace gle
{

/* *************************** load_gl_extensions ************************** */

bool
load_gl_extensions ()
{
  LOAD_GL_EXTENSION (glGetStringi, PFNGLGETSTRINGIPROC);

  LOAD_GL_EXTENSION (glGenFramebuffers, PFNGLGENFRAMEBUFFERSPROC);
  LOAD_GL_EXTENSION (glDeleteFramebuffers, PFNGLDELETEFRAMEBUFFERSPROC);
  LOAD_GL_EXTENSION (glBindFramebuffer, PFNGLBINDFRAMEBUFFERPROC);
  LOAD_GL_EXTENSION (glFramebufferTexture2D, PFNGLFRAMEBUFFERTEXTURE2DPROC);

  LOAD_GL_EXTENSION (glCreateShader, PFNGLCREATESHADERPROC);
  LOAD_GL_EXTENSION (glDeleteShader, PFNGLDELETESHADERPROC);
  LOAD_GL_EXTENSION (glCompileShader, PFNGLCOMPILESHADERPROC);
  LOAD_GL_EXTENSION (glGetShaderiv, PFNGLGETSHADERIVPROC);
  LOAD_GL_EXTENSION (glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
  LOAD_GL_EXTENSION (glShaderSource, PFNGLSHADERSOURCEPROC);

  LOAD_GL_EXTENSION (glCreateProgram, PFNGLCREATEPROGRAMPROC);
  LOAD_GL_EXTENSION (glDeleteProgram, PFNGLDELETEPROGRAMPROC);
  LOAD_GL_EXTENSION (glLinkProgram, PFNGLLINKPROGRAMPROC);
  LOAD_GL_EXTENSION (glAttachShader, PFNGLATTACHSHADERPROC);
  LOAD_GL_EXTENSION (glDetachShader, PFNGLDETACHSHADERPROC);
  LOAD_GL_EXTENSION (glGetProgramiv, PFNGLGETPROGRAMIVPROC);
  LOAD_GL_EXTENSION (glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC);

  return true;
}

/* ******************************* message_gl ****************************** */

const char *
message_gl (GLenum code)
{
  switch (code)
    {

    case GL_NO_ERROR:
      return err_str_no_error;

    case GL_INVALID_ENUM:
      return err_str_invalid_enum;

    case GL_INVALID_VALUE:
      return err_str_invalid_value;

    case GL_INVALID_OPERATION:
      return err_str_invalid_operation;

    case GL_STACK_OVERFLOW:
      return err_str_stack_overflow;

    case GL_STACK_UNDERFLOW:
      return err_str_stack_underflow;

    case GL_OUT_OF_MEMORY:
      return err_str_out_of_memory;

    default:
      return err_str_empty;

    }
}

}