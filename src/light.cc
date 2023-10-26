#include "light.h"

namespace gle
{

/* ****************************** Light::Light ***************************** */

Light::Light (const Color &color, SceneNode *parent)
    : SceneNode (parent), m_color (color)
{
  //
}

}
