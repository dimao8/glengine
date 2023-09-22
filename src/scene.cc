#include "scene.h"

namespace gle
{

/* **************************** Scene::type_name *************************** */

const std::string
Scene::type_name () const
{
  return "Scene";
}

/* ***************************** Scene::~Scene ***************************** */

Scene::~Scene()
{
  for (auto it : m_node_list)
    delete it;
  m_node_list.clear();
}

} // namespace gle
