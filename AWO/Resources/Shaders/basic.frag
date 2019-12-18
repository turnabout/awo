#version 330 core

in vec2 texCoords;

out vec4 outColor;

uniform sampler2D sprite_sheet;

void main()
{
	outColor = texture(sprite_sheet, texCoords);
}
