#include "light.h"

namespace gle
{

/* ****************************** Light::Light ***************************** */

Light::Light (const Color &color, SceneNode *parent)
    : SceneNode (parent), m_color (color)
{
  //
}

/* **************************** Light::type_name *************************** */

const std::string
Light::type_name () const
{
  return "Light";
}

}
