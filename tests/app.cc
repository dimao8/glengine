#include "../src/application.h"

#include <glm/trigonometric.hpp>

class App : public gle::Application
{

private:
  std::shared_ptr<gle::Shader> m_vertex_shader;
  std::shared_ptr<gle::Shader> m_fragment_shader;
  std::shared_ptr<gle::ShaderProgram> m_shader_program;
  std::shared_ptr<gle::Mesh> m_cube;
  std::shared_ptr<gle::Camera> m_camera;
  std::shared_ptr<gle::Light> m_light;
  std::shared_ptr<gle::Texture> m_texture;

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
  location = m_shader_program->get_uniform_location ("tex");
  glUniform1i (location, 0);

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
  m_vertex_shader = std::shared_ptr<gle::Shader> (
      new gle::Shader (gle::ShaderType::vertex, "tests/shader.vert", true));
  m_fragment_shader = std::shared_ptr<gle::Shader> (
      new gle::Shader (gle::ShaderType::fragment, "tests/shader.frag", true));
  m_shader_program = std::shared_ptr<gle::ShaderProgram> (
      new gle::ShaderProgram (m_vertex_shader, m_fragment_shader));
  m_cube = std::shared_ptr<gle::Mesh> (new gle::Mesh ());
  m_camera = std::shared_ptr<gle::Camera> (new gle::Camera ());
  m_camera->move_position_to (glm::vec3 (2.0f, 4.0f, -2.0f));
  m_camera->move_pov_to (glm::vec3 (0.0f));
  m_camera->update ();

  m_shader_program->enable ();
  m_light = std::shared_ptr<gle::Light> (
      new gle::Light (nullptr, gle::Color (1.0, 1.0, 1.0, 1.0),
                      glm::vec3 (-10.0, 10.0, -10.0)));

  m_texture
      = std::shared_ptr<gle::Texture> (new gle::Texture ("tests/test.tga"));
  m_texture->enable (0);
  m_texture->set_filtering (gle::TextureFilter::linear,
                            gle::TextureFilter::linear);
}

/* ****************************** App::cleanup ***************************** */

void
App::cleanup ()
{
  // TODO : Delete all
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
