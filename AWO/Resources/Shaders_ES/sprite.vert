#version 100

attribute vec2 aPos;
attribute vec2 aTexCoords;
attribute float aPaletteIndex;

varying vec2 texCoords;
varying float paletteIndex;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(aPos, 0.0, 1.0);
	texCoords = aTexCoords;
	paletteIndex = aPaletteIndex;
}
