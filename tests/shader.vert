#version 330 core

layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vnormal;
layout (location = 2) in vec2 vtexcoord;

out vec2 ftexcoord;
out vec3 fnormal;
out vec3 femitter;

uniform vec3 emitter;

uniform mat3 normal_matrix;
uniform mat4 model_matrix;
uniform mat4 model_view_projection_matrix;

void
main ()
{
  vec3 p = vec3 (model_matrix * vec4 (vposition, 1.0));
  femitter = normalize (emitter - p);
  fnormal = normal_matrix * vnormal;
  ftexcoord = vtexcoord;

  gl_Position = model_view_projection_matrix * vec4 (vposition, 1.0);
}
