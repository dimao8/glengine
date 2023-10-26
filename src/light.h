#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "scenenode.h"

namespace gle
{

class Light : public SceneNode
{

public:
  Color m_color; /// Light source color

  Light() = delete;
  Light(const Light &) = delete;
  Light(const Color& color, SceneNode *parent = nullptr);

  ///
  /// \brief Delete light source
  ///
  virtual ~Light () {}
};

}

#endif // LIGHT_H
