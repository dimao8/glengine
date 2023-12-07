#include "scenenode.h"

#include <stdexcept>

namespace gle
{

/* ************************** SceneNode::SceneNode ************************* */

SceneNode::SceneNode (const std::shared_ptr<SceneNode> &parent)
    : m_parent_ptr (parent)
{
  // TODO : Check for parent validity
}

/* ************************* SceneNode::~SceneNode ************************* */

SceneNode::~SceneNode ()
{
  //
}

/* *************************** SceneNode::matrix *************************** */

glm::mat4
SceneNode::matrix () const
{
  if (m_parent_ptr != nullptr)
    return m_parent_ptr->matrix () * m_transform;
  else
    return m_transform;
}

/* **************************** SceneNode::draw **************************** */

void
SceneNode::draw (ShaderProgram &program)
{
  program.enable ();

  for (auto it : m_children)
    it->draw (program);

  // TODO : Draw SceneNode
}

/* *************************** SceneNode::parent *************************** */

const std::shared_ptr<SceneNode> &
SceneNode::parent () const
{
  return m_parent_ptr;
}

}