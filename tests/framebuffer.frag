#version 330 core

in vec2 ftexcoord;

uniform sampler2D tex;

out vec4 color;

void main(void)
{
  color = texture (tex, ftexcoord);
}