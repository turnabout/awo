#version 330 core

in vec2 texCoords;
out vec4 outColor;

uniform sampler2D sprite_sheet;
uniform sampler2D color_table;

void main()
{
	// vec4 textureColor = texture(sprite_sheet, texCoords);
	// float textureVal = textureColor.r;

	// if (outColor.a == 0) {
		// outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
		// return
	// }

	// Temp debug: make transparent pixels red

	// outColor = vec4(textureVal, textureVal, textureVal, 1.0);

	// outColor = texture(sprite_sheet, texCoords);
	outColor = texture(color_table, texCoords);
}
