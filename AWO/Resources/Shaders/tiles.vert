#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 texCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(aPos, 0.0, 1.0);
	// gl_Position = projection * vec4(aPos, 0.0, 1.0);
	// gl_Position = vec4(aPos, 0.0, 1.0);

	// texCoords = aPos;
	texCoords = aTexCoords;
}
