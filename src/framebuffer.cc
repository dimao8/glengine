#include "framebuffer.h"
#include "attribute.h"
#include "buffer.h"
#include "image.h"
#include "shader.h"
#include "shaderprogram.h"
#include "texture.h"
#include "vertexarray.h"

#include <glm/gtc/type_ptr.hpp>

namespace gle
{

const std::string Framebuffer::vertex_source
    = "#version 330 core\n"
      "\n"
      "layout (location = 0) in vec2 vposition;\n"
      "layout (location = 1) in vec2 vtexcoord;\n"
      "\n"
      "uniform mat4 matrix;\n"
      "\n"
      "out vec2 ftexcoord;\n"
      "\n"
      "void main(void)\n"
      "{\n"
      "  ftexcoord = vtexcoord;\n"
      "  gl_Position = matrix * vec4(vposition, 0.0, 1.0);\n"
      "}\n";

const std::string Framebuffer::fragment_source
    = "#version 330 core\n"
      "\n"
      "in vec2 ftexcoord;\n"
      "\n"
      "uniform sampler2D tex;\n"
      "\n"
      "out vec4 color;\n"
      "\n"
      "void main(void)\n"
      "{\n"
      "  color = texture (tex, ftexcoord);\n"
      "}\n";

/* ************************ Framebuffer::Framebuffer *********************** */

Framebuffer::Framebuffer (int width, int height)
    : m_size (width, height), m_color_type (ColorType::rgb),
      m_vertex_shader (new Shader (ShaderType::vertex, vertex_source)),
      m_fragment_shader (new Shader (ShaderType::fragment, fragment_source)),
      m_shader_program (new ShaderProgram (m_vertex_shader, m_fragment_shader))
{
  m_geometry[0] = -1.0;
  m_geometry[1] = -1.0;
  m_geometry[2] = 0.0;
  m_geometry[3] = 0.0;
  m_geometry[4] = 1.0;
  m_geometry[5] = 1.0;
  m_geometry[6] = 1.0;
  m_geometry[7] = 1.0;
  m_geometry[8] = -1.0;
  m_geometry[9] = 1.0;
  m_geometry[10] = 0.0;
  m_geometry[11] = 1.0;
  m_geometry[12] = -1.0;
  m_geometry[13] = -1.0;
  m_geometry[14] = 0.0;
  m_geometry[15] = 0.0;
  m_geometry[16] = 1.0;
  m_geometry[17] = -1.0;
  m_geometry[18] = 1.0;
  m_geometry[19] = 0.0;
  m_geometry[20] = 1.0;
  m_geometry[21] = 1.0;
  m_geometry[22] = 1.0;
  m_geometry[23] = 1.0;

  m_vao
      = std::shared_ptr<VertexArray> (new VertexArray (DrawingMode::triangle));
  m_vao->enable ();
  m_vbo = std::shared_ptr<Buffer> (
      new Buffer (BufferAccess::draw, BufferOptimization::stat, geometry_size,
                  m_geometry.data ()));
  m_vbo->enable ();

  m_matrix = glm::mat4 (1.0);
  m_vao->add_buffer (m_vbo, new Attribute (AttributeType::fv2, 0));
  m_vao->add_buffer (m_vbo, new Attribute (AttributeType::fv2, 1));
  m_vao->update ();

  m_texture = std::shared_ptr<Texture> (
      new Texture (m_size.x, m_size.y, m_color_type));
  m_texture->enable ();

  glGenFramebuffers (1, &m_framebuffer);
  enable ();

  glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                          m_texture->handle (), 0);

  glGenRenderbuffers (1, &m_renderbuffer);
  glBindRenderbuffer (GL_RENDERBUFFER, m_renderbuffer);
  glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                             GL_RENDERBUFFER, m_renderbuffer);
}

/* *********************** Framebuffer::~Framebuffer *********************** */

Framebuffer::~Framebuffer ()
{
  glDeleteRenderbuffers (1, &m_renderbuffer);
  glDeleteFramebuffers (1, &m_framebuffer);
}

/* ************************** Framebuffer::enable ************************** */

void
Framebuffer::enable ()
{
  glBindFramebuffer (GL_FRAMEBUFFER, m_framebuffer);
}

/* *************************** Framebuffer::draw *************************** */

void
Framebuffer::draw ()
{
  disable ();

  m_texture->enable (0);

  glClear (GL_COLOR_BUFFER_BIT);

  m_shader_program->enable ();

  GLint location = m_shader_program->get_uniform_location ("matrix");
  glUniformMatrix4fv (location, 1, GL_FALSE, glm::value_ptr<float> (m_matrix));
  location = m_shader_program->get_uniform_location ("tex");
  glUniform1i (location, 0);
  m_vao->enable ();
  glDisable(GL_DEPTH_TEST);
  m_vao->draw (*m_shader_program);
  glEnable(GL_DEPTH_TEST);

  enable ();
}

/* *********************** Framebuffer::save_to_file *********************** */

void
Framebuffer::save_to_file (const std::string &file_name)
{
  enable ();

  uint8_t *framebuffer_ptr
      = new uint8_t[m_size.x * m_size.y * Color::color_size (m_color_type)];

  glReadPixels (0, 0, m_size.x, m_size.y, Color::color_type_gl (m_color_type),
                GL_UNSIGNED_BYTE, framebuffer_ptr);
  Image img (m_size.x, m_size.y, m_color_type, framebuffer_ptr, true);
  img.save (file_name);
}

/* ************************** Framebuffer::disable ************************* */

void
Framebuffer::disable ()
{
  glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

}