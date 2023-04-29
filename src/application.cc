#include <application.h>
#include <logger.h>

#include <iostream>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include "opengl.h"

#define DEFAULT_CLIENT_WIDTH 800
#define DEFAULT_CLIENT_HEIGHT 600

namespace gle
{

/* ************************ Application::Application *********************** */

Application::Application (int argc, char **argv) : m_should_close (true)
{
  LOG_PRINT (SeverityLevel::info, "Parse arguments\n");
  parse_arguments (argc, argv);

  // Try to init glfw3
  LOG_PRINT (SeverityLevel::info, "Init glfw3\n");
  if (!glfwInit ())
    {
      LOG_PRINT (SeverityLevel::error, "Can not init glfw3\n");
      return;
    }
  LOG_PRINT (SeverityLevel::info, "GLFW version: %s\n",
             glfwGetVersionString ());

  // Try to create window
  LOG_PRINT (SeverityLevel::info, "Create main window\n");

  glfwWindowHint (GLFW_RESIZABLE, 1);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, 1);
  glfwWindowHint (GLFW_DOUBLEBUFFER, 1);
  glfwWindowHint (GLFW_RED_BITS, 8);
  glfwWindowHint (GLFW_GREEN_BITS, 8);
  glfwWindowHint (GLFW_BLUE_BITS, 8);
  glfwWindowHint (GLFW_ALPHA_BITS, 8);
  glfwWindowHint (GLFW_DEPTH_BITS, 24);
  glfwWindowHint (GLFW_STENCIL_BITS, 8);
  glfwWindowHint (GLFW_RESIZABLE, 0);

  m_window = glfwCreateWindow (DEFAULT_CLIENT_WIDTH, DEFAULT_CLIENT_HEIGHT,
                               PACKAGE " " VERSION, 0, 0);
  if (m_window == nullptr)
    {
      LOG_PRINT (SeverityLevel::error, "Can not create main window\n");
      return;
    }
  glfwMakeContextCurrent (m_window);

  if (!load_gl_extensions ())
    {
      LOG_PRINT (SeverityLevel::error, "Error while extensions loading\n");
      return;
    }

  // Get OpenGL info
  GLint version_major, version_minor, no_of_ext;
  LOG_PRINT (SeverityLevel::info, "Device: %s\n", glGetString (GL_RENDERER));
  LOG_PRINT (SeverityLevel::info, "Vendor: %s\n", glGetString (GL_VENDOR));
  glGetIntegerv (GL_MAJOR_VERSION, &version_major);
  glGetIntegerv (GL_MINOR_VERSION, &version_minor);
  LOG_PRINT (SeverityLevel::info, "GL Version: %i.%i\n", version_major,
             version_minor);
  LOG_PRINT (SeverityLevel::info, "GLSL Version: %s\n",
             glGetString (GL_SHADING_LANGUAGE_VERSION));
  glGetIntegerv (GL_NUM_EXTENSIONS, &no_of_ext);
  LOG_PRINT (SeverityLevel::info, "Extensions: \n");
  for (auto n = 0; n < no_of_ext; n++)
    {
      LOG_PRINT (SeverityLevel::none, "  %s\n",
                 glGetStringi (GL_EXTENSIONS, n));
    }

  // TODO : Further application init

  m_should_close = false;
}

/* *********************** Application::~Application *********************** */

Application::~Application ()
{
  cleanup ();

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
Application::cleanup ()
{
  // TODO : Clean further

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
    }

  if (m_should_close)
    return 0;

  while (!glfwWindowShouldClose (m_window))
    {
      glfwPollEvents ();

      draw ();

      glfwSwapBuffers (m_window);
    }

  // TODO : Run the application

  return 0;
}

/* *************************** Application::draw *************************** */

void
Application::draw ()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TODO : Draw further
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

} // namespace gle
