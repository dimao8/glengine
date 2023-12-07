#include "../src/application.h"
#include "../src/logger.h"
#include "../src/sceneadapter.h"

#include <glm/trigonometric.hpp>

class App : public gle::Application
{

private:
  std::shared_ptr<gle::Shader> m_vertex_shader;
  std::shared_ptr<gle::Shader> m_fragment_shader;
  std::shared_ptr<gle::ShaderProgram> m_shader_program;
  std::shared_ptr<gle::Scene> m_scene;

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
  m_scene->draw ();
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

  m_scene = std::make_shared<gle::Scene> ();
  gle::SceneAdapter adapter (m_scene);
  if (!adapter.from_gltf ("tests/dice.gltf"))
    {
      gle::logger << gle::SeverityLevel::warning
                  << "There was an error during scene initialization. The "
                     "Scene object was reset to default."
                  << std::endl;
    }

  gle::logger << gle::SeverityLevel::info << "Scene info:" << std::endl;
  gle::logger << m_scene->get_info () << std::endl;
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
