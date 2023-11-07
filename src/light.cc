#include "light.h"

#include <glm/gtc/type_ptr.hpp>

namespace gle
{

/* ****************************** Light::Light ***************************** */

Light::Light (const std::shared_ptr<SceneNode> &parent, const Color &color,
              const glm::vec3 &position)
    : SceneNode (parent), m_color (color), m_position (position)
{
  //
}

/* ***************************** Light::move_to **************************** */

void
Light::move_to (const glm::vec3 &pos)
{
  m_position = pos;
}

/* **************************** Light::position **************************** */

const float *
Light::position_ptr () const
{
  return glm::value_ptr<float> (m_position);
}

/* **************************** Light::color_ptr *************************** */

const float *
Light::color_ptr () const
{
  return m_color.color_ptr ();
}

}
