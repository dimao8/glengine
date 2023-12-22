#include "scene.h"

namespace gle
{

/* ****************************** Scene::Scene ***************************** */

Scene::Scene ()
{
  // ctor
}

/* ***************************** Scene::~Scene ***************************** */

Scene::~Scene ()
{
  for (auto it : m_nodes)
    delete it;
}

/* ****************************** Scene::reset ***************************** */

void
Scene::reset ()
{
  m_nodes.clear ();

  m_info.clear ();
  m_info.push_back ("Default scene");
}

/* ****************************** Scene::draw ****************************** */

void
Scene::draw ()
{
  //
}

/* **************************** Scene::get_info **************************** */

const std::vector<std::string> &
Scene::get_info () const
{
  return m_info;
}

} // namespace gle
