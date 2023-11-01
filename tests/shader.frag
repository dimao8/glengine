#version 330 core

in vec2 ftexcoord;
in vec3 fnormal;
in vec3 femitter;

uniform vec4 emitter_color;

uniform sampler2D tex;

out vec4 color;

void main()
{
  vec3 c = vec3(emitter_color) * max (dot (fnormal, femitter), 0.0);
  color = vec4(c, 1.0);
  //color = vec4(fnormal, 1.0);
}
