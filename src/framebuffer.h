#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "opengl.h"
#include "color.h"

#include <memory>
#include <string>
#include <array>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

namespace gle
{

class Shader;
class ShaderProgram;
class VertexArray;
class Buffer;
class Texture;

class Framebuffer
{

private:

  static const std::string vertex_source;
  static const std::string fragment_source;
  static constexpr size_t geometry_size = 24;

public:

  static void disable ();

private:

  glm::ivec2 m_size;
  ColorType m_color_type;

  std::shared_ptr<Shader> m_vertex_shader;
  std::shared_ptr<Shader> m_fragment_shader;
  std::shared_ptr<ShaderProgram> m_shader_program;
  std::shared_ptr<Buffer> m_vbo;
  std::shared_ptr<VertexArray> m_vao;
  std::shared_ptr<Texture> m_texture;
  std::array<float, geometry_size> m_geometry;
  glm::mat4 m_matrix;
  GLuint m_renderbuffer;
  GLuint m_framebuffer;

public:

  Framebuffer () = delete;
  Framebuffer (const Framebuffer &) = delete;
  Framebuffer (int width, int height);
  virtual ~Framebuffer ();
  void enable ();
  void draw ();
  void save_to_file (const std::string & file_name);

};

}

#endif // FRAMEBUFFER_H
