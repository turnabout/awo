#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

void main()
{
	gl_Position = vec4(vertex.xy, 0.0, 1.0);
}
