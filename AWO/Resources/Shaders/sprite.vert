#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in float aPaletteIndex;

out vec2 texCoords;
out float paletteIndex;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(aPos, 0.0, 1.0);
	texCoords = aTexCoords;
	paletteIndex = aPaletteIndex;
}
