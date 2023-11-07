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

const std::string Application::framebuffer_vertex_source
    = "#version 330 core\n"
      "\n"
      "layout (location = 0) in vec2 vposition;\n"
      "layout (location = 1) in vec2 vtexcoord;\n"
      "\n"
      "uniform mat4 matrix;\n"
      "\n"
      "out vec2 ftexcoord;\n"
      "\n"
      "void main(void)\n"
      "{\n"
      "  ftexcoord = vtexcoord;\n"
      "  gl_Position = matrix * vec4(vposition, 0.0, 1.0);\n"
      "}\n";

const std::string Application::framebuffer_fragment_source
    = "#version 330 core\n"
      "\n"
      "in vec2 ftexcoord;\n"
      "\n"
      "uniform sampler2D tex;\n"
      "\n"
      "out vec4 color;\n"
      "\n"
      "void main(void)\n"
      "{\n"
      "  color = texture (tex, ftexcoord);\n"
      "}\n";

/* ************************ Application::Application *********************** */

Application::Application (int argc, char **argv)
    : m_should_close (true), m_save_framebuffer (false)
{
  LOG_DEBUG (logger << SeverityLevel::info << _ ("Parse arguments")
                    << std::endl);
  parse_arguments (argc, argv);

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

  m_window = glfwCreateWindow (DEFAULT_CLIENT_WIDTH, DEFAULT_CLIENT_HEIGHT,
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
  m_fbo_mesh[0] = -1.0;
  m_fbo_mesh[1] = -1.0;
  m_fbo_mesh[2] = 0.0;
  m_fbo_mesh[3] = 0.0;
  m_fbo_mesh[4] = 1.0;
  m_fbo_mesh[5] = 1.0;
  m_fbo_mesh[6] = 1.0;
  m_fbo_mesh[7] = 1.0;
  m_fbo_mesh[8] = -1.0;
  m_fbo_mesh[9] = 1.0;
  m_fbo_mesh[10] = 0.0;
  m_fbo_mesh[11] = 1.0;
  m_fbo_mesh[12] = -1.0;
  m_fbo_mesh[13] = -1.0;
  m_fbo_mesh[14] = 0.0;
  m_fbo_mesh[15] = 0.0;
  m_fbo_mesh[16] = 1.0;
  m_fbo_mesh[17] = -1.0;
  m_fbo_mesh[18] = 1.0;
  m_fbo_mesh[19] = 0.0;
  m_fbo_mesh[20] = 1.0;
  m_fbo_mesh[21] = 1.0;
  m_fbo_mesh[22] = 1.0;
  m_fbo_mesh[23] = 1.0;

  m_fbo_vertex_shader = std::shared_ptr<Shader> (
      new Shader (ShaderType::vertex, framebuffer_vertex_source));
  m_fbo_fragment_shader = std::shared_ptr<Shader> (
      new Shader (ShaderType::fragment, framebuffer_fragment_source));
  m_fbo_shader_program = std::shared_ptr<ShaderProgram> (
      new ShaderProgram (m_fbo_vertex_shader, m_fbo_fragment_shader));
  m_fbo_vao
      = std::shared_ptr<VertexArray> (new VertexArray (DrawingMode::triangle));
  m_fbo_vao->enable ();
  m_fbo_vbo = std::shared_ptr<Buffer> (
      new Buffer (BufferAccess::draw, BufferOptimization::stat,
                  m_fbo_mesh.size () * sizeof (float), m_fbo_mesh.data ()));
  m_fbo_matrix = glm::mat4 (1.0);
  m_fbo_vao->add_buffer (m_fbo_vbo, new Attribute (AttributeType::fv2, 0));
  m_fbo_vao->add_buffer (m_fbo_vbo, new Attribute (AttributeType::fv2, 1));

  int w, h;
  glfwGetFramebufferSize (m_window, &w, &h);
  m_framebuffer_size = glm::uvec2 (w, h);

  // Color framebuffer texture
  glGenFramebuffers (1, &m_framebuffer);
  glBindFramebuffer (GL_FRAMEBUFFER, m_framebuffer);

  glGenTextures (1, &m_framebuffer_color_texture);
  glBindTexture (GL_TEXTURE_2D, m_framebuffer_color_texture);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, m_framebuffer_size.x,
                m_framebuffer_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  // glBindTexture (GL_TEXTURE_2D, 0);

  glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                          m_framebuffer_color_texture, 0);

  // Depth-stencil framebuffer texture
  glGenRenderbuffers (1, &m_renderbuffer);
  glBindRenderbuffer (GL_RENDERBUFFER, m_renderbuffer);
  glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
  glBindRenderbuffer (GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                             GL_RENDERBUFFER, m_renderbuffer);

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
  // TODO : Clean further -->
  glDeleteFramebuffers (1, &m_framebuffer);
  glDeleteRenderbuffers (1, &m_renderbuffer);
  glDeleteTextures (1, &m_framebuffer_color_texture);
  // <--

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

      glBindFramebuffer (GL_FRAMEBUFFER, m_framebuffer);

      p_draw ();

      if (m_save_framebuffer)
        {
          uint8_t *framebuffer_ptr
              = new uint8_t[m_framebuffer_size.x * m_framebuffer_size.y * 3];

          glReadPixels (0, 0, m_framebuffer_size.x, m_framebuffer_size.y,
                        GL_RGB, GL_UNSIGNED_BYTE, framebuffer_ptr);
          Image img (m_framebuffer_size.x, m_framebuffer_size.y,
                     ColorType::rgb, framebuffer_ptr, true);
          img.save ("framebuffer.tga");

          glfwSetWindowShouldClose (m_window, 1);

          break;
        }
      else
        fbo_pass ();

      glfwSwapBuffers (m_window);
    }

  glBindFramebuffer (GL_FRAMEBUFFER, 0);

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

/* ************************* Application::fbo_pass ************************* */

void
Application::fbo_pass ()
{
  glBindFramebuffer (GL_FRAMEBUFFER, 0);
  glBindTexture (GL_TEXTURE_2D, m_framebuffer_color_texture);
  glClear (GL_COLOR_BUFFER_BIT);
  m_fbo_shader_program->enable ();
  GLint location = m_fbo_shader_program->get_uniform_location ("matrix");
  glUniformMatrix4fv (location, 1, GL_FALSE,
                      glm::value_ptr<float> (m_fbo_matrix));
  m_fbo_vao->enable ();
  m_fbo_vao->draw (*m_fbo_shader_program);
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
