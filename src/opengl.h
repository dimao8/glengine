///
/// \file opengl.h
/// \brief OpenGL common function prototypes
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

#ifndef OPENGL_H
#define OPENGL_H

#include <GL/gl.h>
#include <GL/glext.h>

extern PFNGLGETSTRINGIPROC glGetStringi;
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLSHADERSOURCEPROC glShaderSource;

extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

namespace gle
{

///
/// \brief Load OpenGL extension functions needed by engine
/// \return Return \c false when loading is fail otherwise return \c true
///
bool load_gl_extensions();

///
/// \brief Return constant string with error description text
/// \param [in] code -- Code of the error. If code is not a valid error code,
/// an empty string will be returned
/// \return Return error code string
///
const char* message_gl(GLenum code);

}

#endif // OPENGL_H
