#include "../src/application.h"

class App : public gle::Application
{

private:

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

}

/* ******************************* App::init ******************************* */

void
App::init ()
{
  
}

/* ****************************** App::cleanup ***************************** */

void
App::cleanup ()
{
  
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
