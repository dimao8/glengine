#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace gle
{

/* ***************************** Camera::Camera **************************** */

Camera::Camera (const std::shared_ptr<SceneNode> &parent, float fovy,
                float aspect, float znear, float zfar)
    : SceneNode (parent), m_fovy (fovy), m_aspect (aspect), m_znear (znear),
      m_zfar (zfar), m_position (-5.0f, 1.0f, 2.0f), m_pov (0.0f, 0.0f, 0.0f)
{
  update ();
}

/* ***************************** Camera::Camera **************************** */

Camera::Camera (const Camera &camera) : SceneNode (camera.parent ())
{
  m_position = camera.m_position;
  m_view = camera.m_view;
  m_projection = camera.projection ();
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

/* ************************** Camera::perspective ************************** */

void
Camera::perspective (float fovy, float aspect, float znear, float zfar)
{
  m_projection = glm::perspective (fovy, aspect, znear, zfar);
}

/* ************************** Camera::orthographic ************************* */

void
Camera::orthographic (float left, float right, float bottom, float top,
                      float znear, float zfar)
{
  m_projection = glm::ortho (left, right, bottom, top, znear, zfar);
}

/* ***************************** Camera::update **************************** */

void
Camera::update ()
{
  perspective (m_fovy, m_aspect, m_znear, m_zfar);
  m_view = glm::lookAt (m_position, m_pov, glm::vec3 (0.0f, 1.0f, 0.0f));
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