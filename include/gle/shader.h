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
  /// \brief Compile current shader
  /// \return Return result of the compilation
  ///
  /// Compile current shader and return result of the compilation. If
  /// shader is compiled successfully, it's state is set to
  /// ShaderState::compiled. Otherwise it's state set to ShaderState::source.
  ///
  bool compile ();
};

}

#endif // SHADER_H
