/**
 * \file application.h
 *
 * Application class
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
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
  std::list<Argument> m_args;          /// Argument list
  std::list<Argument> m_accepted_args; /// Accepted argument list
  glm::uvec2 m_framebuffer_size;       /// Framebuffer size
  bool m_save_framebuffer;

  // Internal application state
  bool m_should_close; /// State of the application. Set to true to exit
                       /// application

  // Native variables
  GLFWwindow *m_window; /// GLFW main window handle
  GLuint m_framebuffer; /// Framebuffer object
  GLuint m_framebuffer_texture; /// Framebuffer texture object

  /**
   * \brief Parse arguments and create argument list
   *
   * \param [in] argc -- Number of the arguments in the argument list
   * \param [in] argv -- Argument list
   */
  void parse_arguments (int argc, char **argv);

  /**
   * Clean all resources
   */
  void cleanup ();

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
   * Destroy aplication
   */
  virtual ~Application ();

  /**
   * Register argument as acceptable.
   *
   * \param [in] sname -- Short name of the argument. If it is 0, there is no
   * short argument
   * \param [in] lname -- Long name of the argument. If it is empty, there is
   * no long argument
   * \param [in] comment -- Comment prompt
   */
  void register_arg (char sname, const std::string &lname,
                     const std::string &comment);

  /**
   * Start application
   *
   * \return Returns result of application execution
   */
  int run ();

  /**
   * Draw frame
   */
  void draw ();

  /**
   * Usage prompt of the application
   */
  virtual void usage ();

  /**
   * Version prompt of the application
   */
  virtual void version ();
};

} // namespace gle

#endif // APPLICATION_H
