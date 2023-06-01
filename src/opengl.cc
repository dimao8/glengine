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

  return true;
}

}