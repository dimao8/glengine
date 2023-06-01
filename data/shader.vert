#version 330 core

layout(location=0) in vec3 vposition;
layout(location=0) in vec4 vcolor;

out vec4 fcolor;

uniform mat4 projection;

void main()
{
  gl_Position = projection*vec4(vposition, 1.0);

  fcolor = vcolor;
}
