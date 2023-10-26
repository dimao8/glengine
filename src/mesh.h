#ifndef MESH_H
#define MESH_H

#include "scenenode.h"
#include "buffer.h"
#include "vertexarray.h"

#include <vector>

namespace gle
{
  
class Mesh : public SceneNode
{

private:

  std::vector<Buffer *> m_buffers;
  VertexArray m_vertex_array;

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
