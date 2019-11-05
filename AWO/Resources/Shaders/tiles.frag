#version 330 core

in vec2 texCoords;
out vec4 outColor;

uniform sampler2D sprite_sheet;
// uniform sampler2D palettes_texture;

void main()
{
	// Get greyscale color from raw texture
	// vec4 greyScaleColor = texture(sprite_sheet, vec2(0.0, 0.5));
	vec4 greyScaleColor = texture(sprite_sheet, texCoords);

	// Index into palette
	// vec2 palette_index = vec2(greyScaleColor.r, paletteIndex);
	// outColor = vec4(texture(palettes_texture, palette_index).rgb, greyScaleColor.a);


	outColor = greyScaleColor;
	// outColor = vec4(1.0, 1.0, 1.0, 1.0);
}
