#include <gle/engine.h>
#include <iostream>

class Game : public gle::Application
{

private:
  gle::Shader *m_vertex_shader;
  gle::Shader *m_fragment_shader;
  gle::ShaderProgram *m_shader_program;

public:
  Game (int argc, char **argv);
  virtual ~Game ();
  virtual void init () final;
  void cleanup () final;
};

/* ******************************* Game::Game ****************************** */

Game::Game (int argc, char **argv) : gle::Application (argc, argv) {}

/* ****************************** Game::~Game ****************************** */

Game::~Game ()
{
  cleanup();
}

/* ******************************* Game::init ****************************** */

void
Game::init ()
{
  m_vertex_shader
      = new gle::Shader (gle::ShaderType::vertex, "tests/shader.vert");
  m_fragment_shader
      = new gle::Shader (gle::ShaderType::fragment, "tests/shader.frag");

  m_shader_program = new gle::ShaderProgram (m_vertex_shader, m_fragment_shader);
}

/* ***************************** Game::cleanup ***************************** */

void
Game::cleanup ()
{
  delete m_shader_program;
  delete m_vertex_shader;
  delete m_fragment_shader;
}

/* ******************************** int main ******************************* */

int
main (int argc, char **argv)
{
  Game game (argc, argv);

  game.register_arg ('h', "help", "Print this message and exit");
  game.register_arg ('v', "version", "Print version prompt and exit");

  return game.run ();
}
