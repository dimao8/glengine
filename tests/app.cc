#include <gle/engine.h>

#include <iostream>

int
main (int argc, char **argv)
{
  if (gle::init (argc, argv))
    {
      // Code here
    }

  return gle::terminate ();
}
