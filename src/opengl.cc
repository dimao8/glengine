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
#include "logger.h"
#include "translate.h"

#include <GLFW/glfw3.h>

#ifdef NDEBUG
#define LOAD_GL_EXTENSION(x, y)                                               \
  x = reinterpret_cast<y> (glfwGetProcAddress (#x));                          \
  if (x == nullptr)                                                           \
    {                                                                         \
      logger << SeverityLevel::error << _ ("Can not load ``") << #x           \
             << "\'\'\n"                                                      \
             << std::endl;                                                    \
      return false;                                                           \
    }
#else
#define LOAD_GL_EXTENSION(x, y)                                               \
  x = reinterpret_cast<y> (glfwGetProcAddress (#x));                          \
  if (x == nullptr)                                                           \
    {                                                                         \
      logger << SeverityLevel::error << _ ("Can not load ``") << #x           \
             << "\'\'\n"                                                      \
             << std::endl;                                                    \
      return false;                                                           \
    }                                                                         \
  else                                                                        \
    {                                                                         \
      logger << SeverityLevel::info << "``" << #x << _ ("\'\' was loaded")    \
             << std::endl;                                                    \
    }
#endif // NDEBUG

PFNGLGETSTRINGIPROC glGetStringi = nullptr;

PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = nullptr;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = nullptr;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = nullptr;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = nullptr;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = nullptr;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = nullptr;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = nullptr;

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
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;

PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = nullptr;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = nullptr;

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
PFNGLUNIFORM1IPROC glUniform1i = nullptr;
PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;

const char *err_str_no_error = _ ("No error");
const char *err_str_invalid_enum = _ ("Invalid enumerator");
const char *err_str_invalid_value = _ ("Invalid value");
const char *err_str_invalid_operation = _ ("Invalid operation");
const char *err_str_stack_overflow = _ ("Stack overflow");
const char *err_str_stack_underflow = _ ("Stack underflow");
const char *err_str_out_of_memory = _ ("Out of memory");
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
  LOAD_GL_EXTENSION (glGenRenderbuffers, PFNGLGENRENDERBUFFERSPROC);
  LOAD_GL_EXTENSION (glDeleteRenderbuffers, PFNGLDELETERENDERBUFFERSPROC);
  LOAD_GL_EXTENSION (glBindRenderbuffer, PFNGLBINDRENDERBUFFERPROC);
  LOAD_GL_EXTENSION (glRenderbufferStorage, PFNGLRENDERBUFFERSTORAGEPROC);
  LOAD_GL_EXTENSION (glGetRenderbufferParameteriv,
                     PFNGLGETRENDERBUFFERPARAMETERIVPROC);
  LOAD_GL_EXTENSION (glFramebufferRenderbuffer,
                     PFNGLFRAMEBUFFERRENDERBUFFERPROC);

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
  LOAD_GL_EXTENSION (glUseProgram, PFNGLUSEPROGRAMPROC);

  LOAD_GL_EXTENSION (glGenBuffers, PFNGLGENBUFFERSPROC);
  LOAD_GL_EXTENSION (glBindBuffer, PFNGLBINDBUFFERPROC);
  LOAD_GL_EXTENSION (glDeleteBuffers, PFNGLDELETEBUFFERSPROC);
  LOAD_GL_EXTENSION (glBufferData, PFNGLBUFFERDATAPROC);
  LOAD_GL_EXTENSION (glBufferSubData, PFNGLBUFFERSUBDATAPROC);

  LOAD_GL_EXTENSION (glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
  LOAD_GL_EXTENSION (glEnableVertexAttribArray,
                     PFNGLENABLEVERTEXATTRIBARRAYPROC);
  LOAD_GL_EXTENSION (glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC);
  LOAD_GL_EXTENSION (glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC);
  LOAD_GL_EXTENSION (glBindVertexArray, PFNGLBINDVERTEXARRAYPROC);
  LOAD_GL_EXTENSION (glGetVertexAttribiv, PFNGLGETVERTEXATTRIBIVPROC);
  LOAD_GL_EXTENSION (glGetVertexAttribPointerv,
                     PFNGLGETVERTEXATTRIBPOINTERVPROC);

  LOAD_GL_EXTENSION (glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);
  LOAD_GL_EXTENSION (glUniformMatrix3fv, PFNGLUNIFORMMATRIX3FVPROC);
  LOAD_GL_EXTENSION (glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);
  LOAD_GL_EXTENSION (glUniform1i, PFNGLUNIFORM1IPROC);
  LOAD_GL_EXTENSION (glUniform3fv, PFNGLUNIFORM3FVPROC);
  LOAD_GL_EXTENSION (glUniform4fv, PFNGLUNIFORM4FVPROC);

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