#version 330 core

layout(location=0) in vec3 vposition;
layout(location=1) in vec3 vnormal;
layout(location=2) in vec2 vtexcoord;

out vec2 ftexcoord;

uniform mat4 model_view_projection_matrix;

void main()
{
  gl_Position = model_view_projection_matrix*vec4(vposition, 1.0);

  ftexcoord = vtexcoord;
}
