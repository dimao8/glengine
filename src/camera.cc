#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace gle
{

/* ***************************** Camera::Camera **************************** */

Camera::Camera (SceneNode *parent, float aspect)
    : m_position (-5.0f, 1.0f, 2.0f), m_pov (0.0f, 0.0f, 0.0f)
{
  perspective (45.0f, aspect, 0.1f, 10.0f);
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
  m_view = glm::lookAt (m_position, m_pov, glm::vec3 (0.0f, 1.0f, 0.0f));
}

/* ************************ Camera::view_projection ************************ */

glm::mat4
Camera::view_projection () const
{
  return m_projection * m_view;
}

}