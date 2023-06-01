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

namespace gle
{
  
bool load_gl_extensions();

}

#endif // OPENGL_H
