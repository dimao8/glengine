#include "scene.h"

namespace gle
{

/* ***************************** Scene::~Scene ***************************** */

Scene::~Scene()
{
  for (auto it : m_node_list)
    delete it;
  m_node_list.clear();
}

} // namespace gle
