#include "mesh.h"
#include "opengl.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gle
{

const size_t Mesh::cube_data_size = 288;
const GLfloat Mesh::cube_data[Mesh::cube_data_size] = {
  // clang-format off
// x     y      z        vx     vy     vz       s     t
  -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
   0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,

  -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
   0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f,

   0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
   0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,

  -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
   0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
   0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f,

  -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

   0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
   0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f
  // clang-format on
};

/* ******************************* Mesh::Mesh ****************************** */

Mesh::Mesh (SceneNode *parent)
    : SceneNode (parent), m_vertex_array (DrawingMode::triangle), m_model (1.0)
{
  Buffer *buffer = new Buffer (BufferAccess::draw, BufferOptimization::stat,
                               cube_data_size, cube_data);
  m_buffers.push_back (buffer);
  m_vertex_array.add_buffer (buffer, new Attribute (AttributeType::fv3, 0));
  m_vertex_array.add_buffer (buffer, new Attribute (AttributeType::fv3, 1));
  m_vertex_array.add_buffer (buffer, new Attribute (AttributeType::fv2, 2));

  update ();
}

/* ******************************* Mesh::Mesh ****************************** */

Mesh::Mesh (DrawingMode mode, SceneNode *parent)
    : SceneNode (parent), m_vertex_array (mode), m_model (1.0f)
{
  //
}

/* ****************************** Mesh::~Mesh ****************************** */

Mesh::~Mesh ()
{
  m_vertex_array.remove_buffers ();

  for (auto it : m_buffers)
    delete it;
}

/* ****************************** Mesh::update ***************************** */

void
Mesh::update ()
{
  m_vertex_array.update ();
  m_normal = glm::mat3 (glm::transpose (glm::inverse (m_model)));
}

/* ******************************* Mesh::draw ****************************** */

void
Mesh::draw (ShaderProgram &prog, const Camera &camera)
{
  glm::mat4 full_matrix = camera.view_projection () * m_model;

  prog.enable ();
  GLint location = prog.get_uniform_location ("normal_matrix");
  glUniformMatrix3fv (location, 1, GL_FALSE, glm::value_ptr<float> (m_normal));

  location = prog.get_uniform_location ("model_matrix");
  glUniformMatrix4fv (location, 1, GL_FALSE, glm::value_ptr<float> (m_model));

  location = prog.get_uniform_location ("model_view_projection_matrix");
  glUniformMatrix4fv (location, 1, GL_FALSE,
                      glm::value_ptr<float> (full_matrix));

  m_vertex_array.draw (prog);
}

}
