#ifndef MESH_H
#define MESH_H

#include "attribute.h"
#include "buffer.h"
#include "scenenode.h"
#include "vertexarray.h"
#include "camera.h"

#include <glm/mat4x4.hpp>
#include <vector>

namespace gle
{

class ShaderProgram;

class Mesh : public SceneNode
{

private:
  VertexArray m_vertex_array;
  buffer_vector_t m_buffers;
  glm::mat4 m_model;

public:
  ///
  /// \brief Generate cube
  ///
  Mesh (SceneNode *parent = nullptr);

  Mesh (const Mesh &) = delete;

  ///
  /// \brief Create new mesh
  /// \param [in] parent -- Parent mesh
  ///
  Mesh (DrawingMode mode, SceneNode *parent = nullptr);

  ///
  /// \brief Delete mesh
  ///
  virtual ~Mesh ();

  void update ();

  ///
  /// \brief Draw mesh
  ///
  virtual void draw (ShaderProgram & prog, const Camera& camera);

private:

  static const size_t cube_data_size;
  static const GLfloat cube_data[];

};

} // namespace gle

#endif // MESH_H
