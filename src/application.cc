///
/// \file application.cc
/// \brief Application class implementation
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

#include "application.h"
#include "image.h"
#include "logger.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include "opengl.h"
#include "translate.h"

#define DEFAULT_CLIENT_WIDTH 800
#define DEFAULT_CLIENT_HEIGHT 600

namespace gle
{

/* ************************ Application::Application *********************** */

Application::Application (const std::string &appname,
                          const std::string &appversion, int argc, char **argv)
    : m_appname (appname), m_appversion (appversion), m_should_close (true),
      m_save_framebuffer (false),
      m_framebuffer_size (DEFAULT_CLIENT_WIDTH, DEFAULT_CLIENT_HEIGHT)
{
  logger << SeverityLevel::info << "Start " << m_appname << " " << m_appversion
         << std::endl;
  LOG_DEBUG (logger << SeverityLevel::info << _ ("Parse arguments")
                    << std::endl);
  parse_arguments (argc, argv);

  // Init dirs
  dirs.set_application_name (m_appname);
  dirs.data_search ();
  dirs.config_search ();
  dirs.bin_search ();

  // Try to init glfw3
  LOG_DEBUG (logger << SeverityLevel::info << _ ("Init glfw3") << std::endl);
  if (!glfwInit ())
    {
      logger << SeverityLevel::error << _ ("Can not init glfw3") << std::endl;
      return;
    }
  LOG_DEBUG (logger << SeverityLevel::info << _ ("GLFW version: ")
                    << glfwGetVersionString () << std::endl);

  // Try to create window
  LOG_DEBUG (logger << SeverityLevel::info << "Create main window"
                    << std::endl);

  // glfwWindowHint (GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, 1);
  glfwWindowHint (GLFW_RED_BITS, 8);
  glfwWindowHint (GLFW_GREEN_BITS, 8);
  glfwWindowHint (GLFW_BLUE_BITS, 8);
  glfwWindowHint (GLFW_ALPHA_BITS, 8);
  glfwWindowHint (GLFW_DEPTH_BITS, 24);
  glfwWindowHint (GLFW_STENCIL_BITS, 8);
  glfwWindowHint (GLFW_RESIZABLE, 0);
#ifndef NDEBUG
  glfwWindowHint (GLFW_OPENGL_DEBUG_CONTEXT, 1);
#endif // NDEBUG

  m_window = glfwCreateWindow (m_framebuffer_size.x, m_framebuffer_size.y,
                               PACKAGE " " VERSION, 0, 0);
  if (m_window == nullptr)
    {
      logger << SeverityLevel::error << _ ("Can not create main window")
             << std::endl;
      return;
    }
  glfwMakeContextCurrent (m_window);

  if (!load_gl_extensions ())
    {
      logger << SeverityLevel::error << _ ("Error while extensions loading")
             << std::endl;
      return;
    }

  glfwSetWindowUserPointer (m_window, this);
  glfwSetFramebufferSizeCallback (m_window, static_framebuffer_size_callback);

// Get OpenGL info
#ifndef NDEBUG
  GLint version_major, version_minor, no_of_ext;
  logger << SeverityLevel::info << _ ("Device: ") << glGetString (GL_RENDERER)
         << std::endl;
  logger << SeverityLevel::info << _ ("Vendor: ") << glGetString (GL_VENDOR)
         << std::endl;
  glGetIntegerv (GL_MAJOR_VERSION, &version_major);
  glGetIntegerv (GL_MINOR_VERSION, &version_minor);
  logger << SeverityLevel::info << _ ("GL Version: ") << version_major << "."
         << version_minor << std::endl;
  logger << SeverityLevel::info << _ ("GLSL Version: ")
         << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl;
  glGetIntegerv (GL_NUM_EXTENSIONS, &no_of_ext);
  logger << SeverityLevel::info << _ ("Extensions: ") << std::endl;
  for (auto n = 0; n < no_of_ext; n++)
    {
      logger << "\t" << glGetStringi (GL_EXTENSIONS, n) << std::endl;
    }
#endif // NDEBUG

  // Generate FBO geometry and shaders
  m_framebuffer = std::shared_ptr<Framebuffer> (
      new Framebuffer (m_framebuffer_size.x, m_framebuffer_size.y));

  glEnable (GL_DEPTH_TEST);
  glEnable (GL_TEXTURE_2D);
  glClearColor (0.75, 0.70, 0.5, 1.0);
  glViewport (0, 0, m_framebuffer_size.x, m_framebuffer_size.y);

  // TODO : Further application init

  m_should_close = false;
}

/* *********************** Application::~Application *********************** */

Application::~Application ()
{
  // TODO : Close application
}

/* ********************** Application::parse_arguments ********************* */

void
Application::parse_arguments (int argc, char **argv)
{
  int n = 0;
  std::string arg;
  std::string lname;
  std::string value;
  char sname;

  if (argc <= 1)
    return;

  std::string::const_iterator it;

  while (true)
    {
      n++;
      if (n >= argc)
        break;

      arg = argv[n];
      it = arg.begin ();
      lname.clear ();
      value.clear ();

      // Check for -
      if (*it != '-')
        continue;
      // Check wether argument is short or long
      it++;
      if (*it == '-') // Long argument
        {
          it++;
          while (*it != '=') // Extract name
            {
              if (it == arg.end ())
                break;
              else
                lname.push_back (*it);
              it++;
            }

          if (it != arg.end ())
            it++;          // Skip =
          if (*it == '\"') // Skip open "
            it++;
          while (it != arg.end ()) // Extract value
            {
              value.push_back (*it);
              it++;
            }
          if (!value.empty ()
              && value[value.size () - 1] == '\"') // Remove close "
            value.pop_back ();
          m_args.emplace_back (lname, 0, value);
        }
      else // Short argument
        {
          sname = *it;
          it++;
          if (it != arg.end ())
            {
              while (it != arg.end ()) // Extract value
                {
                  value.push_back (*it);
                  it++;
                }
            }
          else
            {
              n++;
              if (n >= argc)
                value = "";
              else if (argv[n][0] == '-')
                n--;
              else
                value = argv[n];
              m_args.emplace_back ("", sname, value);
            }
        }
    }
}

/* ************************** Application::cleanup ************************* */

void
Application::p_cleanup ()
{
  cleanup ();

  glfwTerminate ();
}

/* **************************** Application::run *************************** */

int
Application::run ()
{
  for (auto it : m_args)
    {
      if (it.get_long_name () == "--help" || it.get_short_name () == "-h")
        usage ();
      if (it.get_long_name () == "--version" || it.get_short_name () == "-v")
        version ();
      if (it.get_long_name () == "--save-framebuffer"
          || it.get_short_name () == "-s")
        m_save_framebuffer = true;
      else
        m_save_framebuffer = false;
    }

  if (m_should_close)
    {
      return 0;
    }

  init ();

  GLint param;

  while (!glfwWindowShouldClose (m_window))
    {
      glfwPollEvents ();

      m_framebuffer->enable ();

      p_draw ();

      if (m_save_framebuffer)
        {
          m_framebuffer->save_to_file ("framebuffer.tga");

          glfwSetWindowShouldClose (m_window, 1);

          break;
        }
      else
        m_framebuffer->draw ();

      glfwSwapBuffers (m_window);
    }

  Framebuffer::disable ();

  // TODO : Run the application

  return 0;
}

/* *************************** Application::draw *************************** */

void
Application::p_draw ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw ();
}

/* *********************** Application::register_arg *********************** */

void
Application::register_arg (char sname, const std::string &lname,
                           const std::string &comment)
{
  m_accepted_args.emplace_back (lname, sname, comment, "");
}

/* *************************** Application::usage ************************** */

void
Application::usage ()
{
  std::cout << "Usage: " << PACKAGE << " [options]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout.flush ();
  for (auto it : m_accepted_args)
    {
      std::cout << "  " << it.get_long_name ();
      std::cout << ", " << it.get_short_name ();
      std::cout << "  " << it.get_comment () << std::endl;
    }
}

/* ************************** Application::version ************************* */

void
Application::version ()
{
  std::cout << PACKAGE << " " << VERSION << std::endl;
}

/* ********************* Application::framebuffer_size ********************* */

void
Application::framebuffer_size (int w, int h)
{
  m_framebuffer_size = glm::uvec2 (w, h);

  // TODO : Recreate framebuffer
}

/* ************* Application::static_framebuffer_size_callback ************* */

void
Application::static_framebuffer_size_callback (GLFWwindow *wnd, int w, int h)
{
  Application *app
      = reinterpret_cast<Application *> (glfwGetWindowUserPointer (wnd));

  app->framebuffer_size (w, h);
}

/* ************************* Application::terminate ************************ */

void
Application::terminate ()
{
  p_cleanup ();
}

} // namespace gle
