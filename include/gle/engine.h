///
/// \file engine.h
/// \brief Main engine header
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

#ifndef GLENGINE_H
#define GLENGINE_H

#include <gle/uuid.h>
#include <string>

namespace gle
{

///
/// \brief Init GL Engine
/// \param [in] argc  -- Number of the arguments
/// \param [in] argv  -- Argument vector
/// \return Return true if init is successful
///
bool init (int argc, char **argv);

///
/// \brief Clear all GL Engine resources
/// \return Return application exit code
///
int terminate ();

///
/// \defgroup constructors Constructors
/// \{
///

///
/// \brief Create image from file
/// \param [in] file_name -- Path to the image file
/// \return Return Image ID or gle::UUID::invalid_uuid
///
const UUID &image_create_from_file (const std::string &file_name);

///
/// \brief Create shader program from files
/// \param [in] vertex_file   -- Path to the vertex shader file
/// \param [in] fragment_file -- Path to the fragment shader file
/// \param [in] geometry_file -- Path to the geometry shader file (can be emtpy)
/// \return Return Shader program ID or gle::UUID::invalid_uuid
///
const UUID &shader_program_create_from_files (const std::string &vertex_file,
                                              const std::string &fragment_file,
                                              const std::string &geometry_file
                                              = "");

///
/// \}
///

///
/// \brief Get object type name
/// \param [in] object_id -- ID of the object
/// \return Return Object type name. If id defines no object, ``none'' will be
/// returned.
///
const std::string object_type_name (const UUID &object_id);

}

#endif // GLENGINE_H