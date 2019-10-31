#version 330 core

in vec2 texCoords;
out vec4 outColor;

uniform sampler2D sprite_sheet;
uniform sampler2D palettes_texture;
uniform float color_table_Y_index; // TEST: temporary, test getting palette index

void main()
{
	vec4 greyScaleColor = texture(sprite_sheet, texCoords);

	// if (outColor.a == 0) {
		// outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
		// return
	// }

	// Temp debug: make transparent pixels red

	// outColor = vec4(textureVal, textureVal, textureVal, 1.0);

	// Index into palette
	vec2 palette_index = vec2(greyScaleColor.r, color_table_Y_index);
	outColor = vec4(texture(palettes_texture, palette_index).rgb, greyScaleColor.a);

	// outColor = greyScaleColor;
	// outColor = texture(sprite_sheet, texCoords);
	// outColor = texture(palettes_texture, texCoords);
}
