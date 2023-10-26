#include "scenenode.h"

#include <stdexcept>

namespace gle
{

/* ************************** SceneNode::SceneNode ************************* */

SceneNode::SceneNode (SceneNode *parent) : m_parent (nullptr)
{
  if (m_parent != nullptr)
    {
      m_parent = parent;

      // TODO : Check for parent validity
    }
}

/* ************************* SceneNode::~SceneNode ************************* */

SceneNode::~SceneNode ()
{
  for (auto it : m_children)
    {
      delete it;
    }
}

/* *************************** SceneNode::matrix *************************** */

glm::mat4
SceneNode::matrix () const
{
  if (m_parent != nullptr)
    return m_parent->matrix () * m_transform;
  else
    return m_transform;
}

/* **************************** SceneNode::draw **************************** */

void
SceneNode::draw (ShaderProgram &program)
{
  // program.enable();

  // for (auto it : m_children)
  //   it->draw(program);

  // TODO : Draw SceneNode
}

}