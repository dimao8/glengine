///
/// \file shaderprogram.h
/// \brief Shader program class header
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

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

namespace gle
{

class Shader;

///
/// \brief Shader program state type
///
enum class ShaderProgramState
{
  empty,   /// Shader program has no shaders inside or shaders are not suitable
  shaders, /// Shader program has valid shaders but not linked. It is also
           /// can determine update the shaders without linkage
  linked   /// Shader program is linked successfully
};

///
/// \brief openGL shader program class
///
class ShaderProgram
{
private:
  unsigned int m_handle; /// Internal OpenGL shader program name

  Shader *m_vertex_shader;   /// Vertex shader pointer
  Shader *m_fragment_shader; /// Fragment shader pointer
  Shader *m_geometry_shader; /// Geometry shader pointer (can be \c nullptr)

  ShaderProgramState m_state; /// Shader program state
public:
  ShaderProgram () = delete;
  ShaderProgram (const ShaderProgram &) = delete;

  ///
  /// \brief Create shader program from shaders
  /// \param [in] vertex    -- Vertex shader pointer
  /// \param [in] fragment  -- Fragment shader pointer
  /// \param [in] geometry  -- Geometry shader pointer (can be \c nullptr)
  ///
  ShaderProgram (Shader *vertex, Shader *fragment, Shader *geometry = nullptr);

  ///
  /// \brief Link current shader program
  /// \return Return result of the linkage
  ///
  /// Link current shader program and return result of the linkage. If
  /// shader program is linked successfully, it's state is set to
  /// ShaderProgramState::linked. Otherwise it's state set to
  /// ShaderProgramState::shaders.
  ///
  bool link ();

  ///
  /// \brief Destroy shader program. Free resources
  ///
  ~ShaderProgram ();
};

}

#endif // SHADERPROGRAM_H