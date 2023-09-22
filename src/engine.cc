///
/// \file engine.cc
/// \brief Engine code
/// \author Khruschev Dmitry aka DimaO
/// \version 0.1
///
/// \copyright Copyright (C) 2023 Khruschev Dmitry aka DimaO
///
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
// USA
//

#include <gle/engine.h>

#include "image.h"
#include "shader.h"
#include "shaderprogram.h"
#include "logger.h"

namespace gle
{

/* ********************************** init ********************************* */

bool
init (int argc, char **argv)
{
  image_create_from_file("tests/test.png");

  // TODO : Init here
  return true;
}

/* ******************************* terminate ******************************* */

int
terminate ()
{
  // TODO : Terminate here
  Object::clear_object_pool ();
  return 0;
}

/* ************************* image_create_from_file ************************ */

const UUID &
image_create_from_file (const std::string &file_name)
{
  Image *image = new Image (file_name);
  // TODO Check for image content
  return image->id ();
}

/* ******************** shader_program_create_from_files ******************* */

const UUID &
shader_program_create_from_files (const std::string &vertex_file,
                                  const std::string &fragment_file,
                                  const std::string &geometry_file)
{
  Shader *vertex = new Shader (ShaderType::vertex, vertex_file);
  if (!vertex->is_compiled ())
    {
      delete vertex;
      return UUID::invalid_uuid;
    }

  Shader *fragment = new Shader (ShaderType::fragment, fragment_file);
  if (!fragment->is_compiled ())
    {
      delete fragment;
      return UUID::invalid_uuid;
    }

  Shader *geometry;
  if (!geometry_file.empty ())
    {
      geometry = new Shader (ShaderType::geometry, geometry_file);
      if (!geometry->is_compiled ())
        {
          delete geometry;
          return UUID::invalid_uuid;
        }
    }

  ShaderProgram *program
      = new ShaderProgram (vertex, fragment, geometry_file.empty () ? nullptr : geometry);
  if (!program->is_linked())
    {
      delete program;
      return UUID::invalid_uuid;
    }

  return program->id();
}

/* **************************** object_type_name *************************** */

const std::string
object_type_name (const UUID &object_id)
{
  if (object_id == UUID::invalid_uuid)
    return "none";

  Object *obj = Object::get_object (object_id);
  if (obj)
    return obj->type_name ();
  else
    return "none";
}

}
