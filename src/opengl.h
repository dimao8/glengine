#ifndef OPENGL_H
#define OPENGL_H

#include <GL/gl.h>
#include <GL/glext.h>

extern PFNGLGETSTRINGIPROC glGetStringi;

namespace gle
{
  
bool load_gl_extensions();

}

#endif // OPENGL_H
