#ifndef MESH_H
#define MESH_H

#include "scenenode.h"
#include "buffer.h"
#include "vertexarray.h"
#include "attribute.h"

#include <vector>

namespace gle
{
  
class Mesh : public SceneNode
{

private:
  VertexArray m_vertex_array;
  buffer_vector_t m_buffers;

public:

  Mesh() = delete;
  Mesh(const Mesh &) = delete;

  ///
  /// \brief Create new mesh
  /// \param [in] parent -- Parent mesh
  ///
  Mesh(DrawingMode mode, SceneNode * parent = nullptr);

  ///
  /// \brief Delete mesh
  ///
  virtual ~Mesh();

  ///
  /// \brief Draw mesh
  ///
  virtual void draw();

};

} // namespace gle


#endif // MESH_H
