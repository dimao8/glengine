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

PFNGLCREATEFRAMEBUFFERSPROC glCreateFramebuffers = nullptr;
PFNGLBINDFRAMEBUFFERPROC glBindFrameBuffer = nullptr;

namespace gle
{

/* *************************** load_gl_extensions ************************** */

bool load_gl_extensions()
{
  LOAD_GL_EXTENSION(glGetStringi, PFNGLGETSTRINGIPROC);

  LOAD_GL_EXTENSION(glCreateFramebuffers, PFNGLCREATEFRAMEBUFFERSPROC);
  LOAD_GL_EXTENSION(glBindFrameBuffer, PFNGLBINDFRAMEBUFFERPROC);

  return true;
}

}