/**
 * \file application.h
 * 
 * Application class
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>
#include <list>
#include <string>

#include "arguments.h"

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
  std::list<Argument> m_args; /// Argument list

  // Internal application state
  bool m_should_close; /// State of the application. Set to true to exit
                       /// application

  // Native variables
  GLFWwindow *m_window; //!< GLFW main window handle

  /**
   * \brief Parse arguments and create argument list
   * 
   * \param [in] argc -- Number of the arguments in the argument list
   * \param [in] argv -- Argument list
   */
  void parse_arguments (int argc, char **argv);

protected:

public:
  /**
   * Create default application
   *
   * \param [in] argc -- Number of the arguments in the argument list
   * \param [in] argv -- Argument list
   */
  Application (int argc = 0, char **argv = nullptr);

  /**
   * Start application
   * 
   * \return Returns result of application execution
   */
  int run();
};

} // namespace gle

#endif // APPLICATION_H
