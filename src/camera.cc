#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace gle
{

/* ***************************** Camera::Camera **************************** */

Camera::Camera (SceneNode *parent)
    : SceneNode (parent), m_type (CameraType::perspective), m_fovy (45.0f),
      m_aspect (1.33f), m_znear (0.1), m_zfar (10.0f), m_left (-1.0f),
      m_right (1.0f), m_bottom (-1.0f), m_top (1.0f),
      m_position (-5.0f, 1.0f, 2.0f), m_pov (0.0f, 0.0f, 0.0f)
{
  m_projection = glm::perspective<float> (m_fovy, m_aspect, m_znear, m_zfar);
  update ();
}

/* ***************************** Camera::Camera **************************** */

Camera::Camera (SceneNode *parent, float fovy, float aspect, float znear,
                float zfar)
    : SceneNode (parent), m_type (CameraType::perspective), m_fovy (fovy),
      m_aspect (aspect), m_znear (znear), m_zfar (zfar), m_left (-1.0f),
      m_right (1.0f), m_bottom (-1.0f), m_top (1.0f),
      m_position (-5.0f, 1.0f, 2.0f), m_pov (0.0f, 0.0f, 0.0f)
{
  m_projection = glm::perspective<float> (m_fovy, m_aspect, m_znear, m_zfar);
  update ();
}

/* ***************************** Camera::Camera **************************** */

Camera::Camera (SceneNode *parent, float left, float right, float bottom,
                float top, float znear, float zfar)
    : SceneNode (parent), m_type (CameraType::orthographic), m_fovy (45.0f),
      m_aspect (1.33f), m_znear (znear), m_zfar (zfar), m_left (left),
      m_right (right), m_bottom (bottom), m_top (top),
      m_position (-5.0f, 1.0f, 2.0f), m_pov (0.0f, 0.0f, 0.0f)
{
  m_projection
      = glm::ortho (m_left, m_right, m_bottom, m_top, m_znear, m_zfar);
  update ();
}

/* ***************************** Camera::Camera **************************** */

Camera::Camera (const Camera &camera)
    : SceneNode (camera.parent ()), m_type (camera.m_type),
      m_position (camera.m_position), m_view (camera.m_view),
      m_projection (camera.m_projection), m_fovy (camera.m_fovy),
      m_aspect (camera.m_aspect), m_zfar (camera.m_zfar),
      m_znear (camera.m_znear), m_left (camera.m_left),
      m_right (camera.m_right), m_bottom (camera.m_bottom),
      m_top (camera.m_top)
{
  update ();
}

/* ************************ Camera::move_position_to *********************** */

void
Camera::move_position_to (const glm::vec3 &v)
{
  m_position = v;
  update ();
}

/* ************************** Camera::move_pov_to ************************** */

void
Camera::move_pov_to (const glm::vec3 &v)
{
  m_pov = v;
  update ();
}

/* ***************************** Camera::update **************************** */

void
Camera::update ()
{
  m_model = glm::mat4 (1.0);
  m_model = glm::scale (m_model, m_scale);

  glm::mat4 rot = glm::mat4_cast (m_rotation);
  glm::mat4 tmp = rot * m_model;

  m_model = glm::translate (tmp, m_translation);
  m_view = glm::translate (rot, m_translation);
}

/* *************************** Camera::projection ************************** */

const glm::mat4 &
Camera::projection () const
{
  return m_projection;
}

/* ************************ Camera::view_projection ************************ */

const glm::mat4
Camera::view_projection () const
{
  return m_projection * m_view;
}

}