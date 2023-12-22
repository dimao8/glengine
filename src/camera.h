#ifndef CAMERA_H
#define CAMERA_H

#include "scenenode.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace gle
{

enum class CameraType
{
  perspective,
  orthographic
};

///
/// \brief Camera class
///
/// \note Camera projection matrix create at start and can not be changed.
/// Update of projection matrix is not need.
///
class Camera : public SceneNode
{

private:
  CameraType m_type;

  // Projection settings
  float m_fovy;
  float m_aspect;
  float m_znear;
  float m_zfar;

  float m_left;
  float m_right;
  float m_bottom;
  float m_top;

  // View settings
  glm::vec3 m_position;
  glm::vec3 m_pov;

  // Matrices
  glm::mat4 m_projection;
  glm::mat4 m_view;

public:
  Camera ();
  Camera (SceneNode *parent, float fovy, float aspect, float znear,
          float zfar);
  Camera (SceneNode *parent, float left, float right, float bottom, float top,
          float znear, float zfar);
  Camera (SceneNode *parent);
  Camera (const Camera &camera);

  void move_position_to (const glm::vec3 &v);
  void move_pov_to (const glm::vec3 &v);

  const glm::mat4 &projection () const;
  const glm::mat4 view_projection () const;

  void update ();
};

}

#endif // CAMERA_H
