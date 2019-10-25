#version 330 core
layout (location = 0) in vec3 pos_vertex;

void main()
{
	gl_Position = vec4(pos_vertex, 1.0);
}
