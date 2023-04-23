#include <glengine.h>

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

  return game.run();
}
