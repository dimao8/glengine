#include "scenenode.h"

#include <stdexcept>

namespace gle
{

/* ************************** SceneNode::SceneNode ************************* */

SceneNode::SceneNode (SceneNode *parent) : m_parent_ptr (parent)
{
  // TODO : Check for parent validity
}

/* ************************* SceneNode::~SceneNode ************************* */

SceneNode::~SceneNode ()
{
  for (auto it : m_children)
    delete it;
}

/* *************************** SceneNode::parent *************************** */

SceneNode *
SceneNode::parent () const
{
  return m_parent_ptr;
}

/* *************************** SceneNode::update *************************** */

void
SceneNode::update ()
{
  m_model = glm::mat4 (1.0);
  m_model = glm::scale (m_model, m_scale);

  glm::mat4 rot = glm::mat4_cast (m_rotation);
  glm::mat4 tmp = rot * m_model;

  m_model = glm::translate (tmp, m_translation);
}

/* **************************** SceneNode::model *************************** */

const glm::mat4
SceneNode::model () const
{
  if (m_parent_ptr == nullptr)
    return m_model;
  else
    return m_parent_ptr->model () * m_model;
}

}