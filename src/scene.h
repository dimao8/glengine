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

  std::vector<std::string> m_info;
  std::list<SceneNode*> m_nodes;

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
  /// \brief Reset scene to default state
  ///
  /// reset() clear all lists and create empty scene with single camera and
  /// cube in the center of the scene.
  ///
  virtual void reset ();

  virtual void draw ();

  const std::vector<std::string> &get_info () const;

  friend class SceneAdapter;
};

}

#endif // SCENE_H
