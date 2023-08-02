#include <gle/engine.h>

#include <iostream>

int
main (int argc, char **argv)
{
  if (gle::init (argc, argv))
    {
      gle::UUID image = gle::image_create_from_file ("tests/test.png");
      std::cout << gle::object_type_name (image) << " = " << image
                << std::endl;
      gle::UUID shader_program = gle::shader_program_create_from_files (
          "tests/vertex.vert", "tests/vertex.frag");
      std::cout << gle::object_type_name (shader_program) << " = " << shader_program
                << std::endl;
    }

  return gle::terminate ();
}
