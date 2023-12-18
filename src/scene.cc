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
  // dtor
}

/* ****************************** Scene::reset ***************************** */

void
Scene::reset ()
{
  m_mesh_list.clear ();
  m_light_list.clear ();
  m_camera_list.clear ();
  m_nodes.clear ();

  m_info.clear ();
  m_info.push_back ("Default scene");

  std::shared_ptr<Camera> camera = std::make_shared<Camera> (nullptr);
  m_nodes.push_back (camera);
  m_camera_list.push_back (camera);
  std::shared_ptr<Light> light = std::make_shared<Light> (
      nullptr, Color (0xFFFFFFFF), glm::vec3 (-10.0f, 10.0f, -2.0f));
  m_nodes.push_back (light);
  m_light_list.push_back (light);
  std::shared_ptr<Mesh> cube = std::make_shared<Mesh> (nullptr);
  m_nodes.push_back (cube);
  m_mesh_list.push_back (cube);
}

/* ****************************** Scene::draw ****************************** */

void
Scene::draw ()
{
  // TODO : Draw scene
}

/* **************************** Scene::get_info **************************** */

const std::vector<std::string> &
Scene::get_info () const
{
  return m_info;
}

} // namespace gle
