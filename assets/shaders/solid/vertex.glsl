#version 150

in vec3 position;
in vec3 color;
in vec2 texcoord;

out vec3 Color;

uniform mat4 trans;

void main()
{
	Color = color;
    gl_Position = trans * vec4(position, 1.0);
}
