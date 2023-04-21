#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

namespace gle
{

/**
 * \brief Application class
 *
 * Application class works with all application infrastructure, e. g.
 * arguments, main window, events etc.
 */
class Application
{

private:
  GLFWwindow *m_window; //!< GLFW main window handle

public:
};

} // namespace gle

#endif // APPLICATION_H
