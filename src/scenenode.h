#ifndef SCENENODE_H
#define SCENENODE_H

#include "shaderprogram.h"

#include <glm/mat4x4.hpp>
#include <list>
#include <memory>
#include <string>

namespace gle
{

///
/// \brief Scene Node class
///
class SceneNode
{

private:
  std::list<SceneNode *> m_children; /// List of children nodes

  std::shared_ptr<SceneNode>
      m_parent_ptr;    /// Parent node (can be nullptr for root node)
  SceneNode *m_parent; /// Parent node (\c nullptr for root)

  glm::mat4 m_transform;    /// Transform matrix (model matrix)

public:

  ///
  /// \brief Create empty scene node
  ///
  SceneNode(SceneNode * parent = nullptr);

  ///
  /// \brief Destroy scene node
  ///
  virtual ~SceneNode();

  ///
  /// \brief Get node model matrix including parent matrices
  /// \return Return node model matrix
  ///
  glm::mat4 matrix () const;

  ///
  /// \brief Draw scene node
  ///
  virtual void draw(ShaderProgram & program);
};

}

#endif // SCENENODE_H
