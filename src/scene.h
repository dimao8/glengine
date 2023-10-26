#ifndef SCENE_H
#define SCENE_H

#include "scenenode.h"

#include <string>
#include <list>

namespace gle
{

///
/// \brief Scene class
///
class Scene
{

private:

  std::list<SceneNode*> m_node_list;

public:

  ///
  /// \brief Create empty scene
  ///
  Scene();

  ///
  /// \brief Delete scene. Free resources
  ///
  virtual ~Scene();

  ///
  /// \brief Draw current scene
  ///
  virtual void draw() {}

};

}

#endif // SCENE_H
