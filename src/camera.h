#ifndef CAMERA_H
#define CAMERA_H

#include "scenenode.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace gle
{

class Camera : public SceneNode
{

private:
  // Projection settings
  float m_fovy;
  float m_aspect;
  float m_znear;
  float m_zfar;

  // View settings
  glm::vec3 m_position;
  glm::vec3 m_pov;

  // Matrices
  glm::mat4 m_projection;
  glm::mat4 m_view;

public:
  Camera (const std::shared_ptr<SceneNode> &parent = nullptr,
          float fovy = 45.0f, float aspect = 1.333333333333f,
          float znear = 0.5f, float zfar = 10.0f);
  Camera (const Camera &camera);

  void move_position_to (const glm::vec3 &v);
  void move_pov_to (const glm::vec3 &v);

  void perspective (float fovy, float aspect, float znear, float zfar);
  void orthographic (float left, float right, float bottom, float top,
                     float znear, float zfar);

  const glm::mat4 &projection () const;
  const glm::mat4 view_projection () const;

  void update ();
};

}

#endif // CAMERA_H
