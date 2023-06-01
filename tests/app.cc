#include <gle/engine.h>

class Game : public gle::Application
{

private:
  gle::Shader *m_vertex_shader;

public:
  Game (int argc, char **argv);
  virtual ~Game () {}
  virtual void init () final;
  virtual void cleanup () final;
};

/* ******************************* Game::Game ****************************** */

Game::Game (int argc, char **argv) : gle::Application (argc, argv) {}

/* ******************************* Game::init ****************************** */

void
Game::init ()
{
  m_vertex_shader = new gle::Shader(gle::ShaderType::vertex, "shader.vert");
}

/* ***************************** Game::cleanup ***************************** */

void
Game::cleanup ()
{
  delete m_vertex_shader;
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
