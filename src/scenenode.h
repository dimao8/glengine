#ifndef SCENENODE_H
#define SCENENODE_H

#include "shaderprogram.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
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

protected:
  std::list<SceneNode*> m_children; /// List of children nodes
  SceneNode *m_parent_ptr; /// Parent node (can be nullptr for root node)

  glm::quat m_rotation;
  glm::vec3 m_scale;
  glm::vec3 m_translation;

  glm::mat4 m_model; /// Transform to world space

public:
  ///
  /// \brief Create empty scene nodse
  ///
  SceneNode (SceneNode *parent = nullptr);

  ///
  /// \brief Destroy scene node
  ///
  virtual ~SceneNode ();

  ///
  /// \brief Get parent node
  ///
  SceneNode *parent () const;

  ///
  /// \brief Update matrices
  ///
  virtual void update ();

  ///
  /// \brief Get model matrix (include parent matrices)
  ///
  const glm::mat4 model () const;

public:
  friend class SceneAdapter;

};

}

#endif // SCENENODE_H
