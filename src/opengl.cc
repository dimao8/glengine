#include "opengl.h"

#include <GLFW/glfw3.h>
#include <logger.h>

#define LOAD_GL_EXTENSION(x, y) \
  x = reinterpret_cast<y>(glfwGetProcAddress(#x)); \
  if (x == nullptr) \
    { \
      LOG_PRINT(SeverityLevel::warning, "Can not load ``%s\'\'\n", #x); \
      return false; \
    }

PFNGLGETSTRINGIPROC glGetStringi = nullptr;

namespace gle
{

/* *************************** load_gl_extensions ************************** */

bool load_gl_extensions()
{
  LOAD_GL_EXTENSION(glGetStringi, PFNGLGETSTRINGIPROC);

  return true;
}

}