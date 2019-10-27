#version 330 core

in vec2 texCoords;
out vec4 color;

uniform sampler2D sprite_sheet;

void main()
{
	color = texture(sprite_sheet, texCoords);

	// Temp debug: make transparent pixels red
	if (color.a == 0) {
		color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}

}
