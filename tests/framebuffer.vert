#version 330 core

layout (location = 0) in vec2 vposition;
layout (location = 1) in vec2 vtexcoord;

uniform mat4 matrix;

out vec2 ftexcoord;

void main(void)
{
  gl_Position = matrix * vposition;
}