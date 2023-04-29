#include <gle/engine.h>

class Game : public gle::Application
{

public:
  Game (int argc, char **argv);
};

/* ******************************* Game::Game ****************************** */

Game::Game (int argc, char **argv) : gle::Application(argc, argv) {}

/* ******************************** int main ******************************* */

int
main (int argc, char **argv)
{
  Game game (argc, argv);

  game.register_arg('h', "help", "Print this message and exit");
  game.register_arg('v', "version", "Print version prompt and exit");

  return game.run();
}
