#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 tex_coords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos_result =  projection * view * vec4(aPos, 0.0, 1.0);

	gl_Position = pos_result;
	tex_coords = aTexCoords;
}
