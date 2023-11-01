#include "../src/application.h"

#include <glm/trigonometric.hpp>

class App : public gle::Application
{

private:
  gle::Shader *m_vertex_shader;
  gle::Shader *m_fragment_shader;
  gle::ShaderProgram *m_shader_program;
  gle::Mesh *m_cube;
  gle::Camera *m_camera;
  gle::Light *m_light;

public:
  App (int argc = 0, char **argv = nullptr);

  virtual void draw ();
  virtual void init ();
  virtual void cleanup ();
};

/* ******************************** App::App ******************************* */

App::App (int argc, char **argv) : gle::Application (argc, argv) {}

/* ******************************* App::draw ******************************* */

void
App::draw ()
{
  GLint location = m_shader_program->get_uniform_location ("emitter");
  glUniform3fv (location, 1, m_light->position_ptr ());
  location = m_shader_program->get_uniform_location ("emitter_color");
  glUniform4fv (location, 1, m_light->color_ptr ());
  m_cube->draw (*m_shader_program, *m_camera);

  static float a = 0;
  m_light->move_to (
      glm::vec3 (10.0f * glm::sin (a), 10.0f, 10.0f * glm::cos (a)));
  a += 0.01;
  if (a > 6.28318530718f)
    a = 0.0f;
}

/* ******************************* App::init ******************************* */

void
App::init ()
{
  m_vertex_shader
      = new gle::Shader (gle::ShaderType::vertex, "tests/shader.vert");
  m_fragment_shader
      = new gle::Shader (gle::ShaderType::fragment, "tests/shader.frag");
  m_shader_program
      = new gle::ShaderProgram (m_vertex_shader, m_fragment_shader);
  m_cube = new gle::Mesh ();
  m_camera = new gle::Camera ();
  m_camera->move_position_to (glm::vec3 (2.0f, 4.0f, -2.0f));
  m_camera->move_pov_to (glm::vec3 (0.0f));
  m_camera->update ();

  m_shader_program->enable ();
  m_light = new gle::Light (nullptr, gle::Color (1.0, 1.0, 1.0, 1.0),
                            glm::vec3 (-10.0, 10.0, -10.0));
}

/* ****************************** App::cleanup ***************************** */

void
App::cleanup ()
{
  delete m_shader_program;
  delete m_vertex_shader;
  delete m_fragment_shader;
  delete m_cube;
  delete m_camera;
  delete m_light;
}

/* ********************************** main ********************************* */

int
main (int argc, char **argv)
{
  App app (argc, argv);
  int result = app.run ();
  app.terminate ();
  return result;
}
