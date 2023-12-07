#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "light.h"
#include "mesh.h"
#include "scenenode.h"

#include <list>
#include <memory>
#include <string>
#include <vector>

namespace gle
{

///
/// \brief Scene class
///
class Scene
{

protected:
  std::vector<std::shared_ptr<Camera> >
      m_camera_list; /// List of the camera nodes
  std::vector<std::shared_ptr<Light> >
      m_light_list; /// List of the light source nodes
  std::vector<std::shared_ptr<Mesh> >
      m_mesh_list;    /// List of the geometry nodes
  std::string m_info; /// Info string

  std::list<std::shared_ptr<SceneNode> > m_nodes;

public:
  ///
  /// \brief Create empty scene
  ///
  Scene ();

  ///
  /// \brief Delete scene. Free resources
  ///
  virtual ~Scene ();

  ///
  /// \brief Draw current scene
  ///
  virtual void draw ();

  ///
  /// \brief Reset scene to default state
  ///
  /// reset() clear all lists and create empty scene with single camera and
  /// cube in the center of the scene.
  ///
  virtual void reset ();

  const std::string &get_info () const;

  friend class SceneAdapter;
};

}

#endif // SCENE_H
