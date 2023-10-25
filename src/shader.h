///
/// \file shader.h
/// \brief Shader class header
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

#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace gle
{

///
/// \brief Shader state type
///
enum class ShaderState
{
  empty,   /// Shader has no source or source is invalid
  source,  /// Shader has source but not compiled. It is also
           /// can determine update the source without compile
  compiled /// Shader is compiled successfully
};

///
/// \brief Shader type
///
enum class ShaderType
{
  vertex,   /// Vertex shader
  geometry, /// Geometry shader
  fragment  /// Fragment shader
};

///
/// \brief openGL shader class
///
class Shader
{

private:
  unsigned int m_handle; /// Internal OpenGL shader name
  ShaderState m_state;   /// Shader state
  ShaderType m_type;     /// Shader type

public:
  Shader () = delete;
  Shader (const Shader &) = delete;

  ///
  /// \brief Load shader from file and compile
  /// \param [in] type -- Type of the shader
  /// \param [in] file_name -- Name of the shader file
  ///
  Shader (ShaderType type, const std::string &file_name);

  ///
  /// \brief Destroy shader. Free resources
  ///
  virtual ~Shader ();

  ///
  /// \brief Compile current shader
  /// \return Return result of the compilation
  ///
  /// Compile current shader and return result of the compilation. If
  /// shader is compiled successfully, it's state is set to
  /// ShaderState::compiled. Otherwise it's state set to ShaderState::source.
  ///
  bool compile ();

  ShaderType get_type () const;
  int get_handle() const;
  bool is_empty () const;
  bool is_compiled () const;

  virtual const std::string type_name() const;
};

}

#endif // SHADER_H
