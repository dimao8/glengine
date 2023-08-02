#version 330 core

layout(location=0) in vec3 vposition;
layout(location=1) in vec4 vcolor;

out vec4 fcolor;

const mat4 projection = mat4(
  1.0, 0.0, 0.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0);

void main()
{
  gl_Position = projection*vec4(vposition, 1.0);

  fcolor = vcolor;
}
