#version 100

attribute vec2 aPos;
attribute vec2 aTexCoords;

varying vec2 tex_coords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos_result =  projection * view * vec4(aPos, 0.0, 1.0);

	gl_Position = pos_result;
	tex_coords = aTexCoords;
}
