#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "scenenode.h"

namespace gle
{

class Light : public SceneNode
{
private:
  Color m_color;        /// Light source color
  glm::vec3 m_position; /// Light source position

public:
  Light () = delete;
  Light (const Light &) = delete;
  Light (const std::shared_ptr<SceneNode> &parent = nullptr,
         const Color &color = Color (0xFFFFFFFF),
         const glm::vec3 &position = glm::vec3 (0.0f, 0.0f, 0.0f));

  ///
  /// \brief Delete light source
  ///
  virtual ~Light () {}

  void move_to (const glm::vec3 &pos);

  const float *position_ptr () const;
  const float *color_ptr () const;
};

}

#endif // LIGHT_H
