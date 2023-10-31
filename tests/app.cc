#include "../src/application.h"

class App : public gle::Application
{

private:
  gle::Shader *m_vertex_shader;
  gle::Shader *m_fragment_shader;
  gle::ShaderProgram *m_shader_program;
  gle::Mesh *m_cube;
  gle::Camera *m_camera;

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
  gle::logger << gle::SeverityLevel::info << "App::draw()" << std::endl;
  m_cube->draw (*m_shader_program, *m_camera);
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
  m_camera->move_position_to (glm::vec3 (1.0f, 5.0f, -1.0f));
  m_camera->move_pov_to (glm::vec3 (0.0f));
  m_camera->update ();
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
