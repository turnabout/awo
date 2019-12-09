#version 100

precision mediump float;

varying vec2 texCoords;
varying float paletteIndex;

uniform sampler2D sprite_sheet;
uniform sampler2D palettes_texture;

void main()
{
	// Get greyscale color from raw texture
	vec4 greyScaleColor = texture2D(sprite_sheet, texCoords);

	// Index into palette
	vec2 palette_index = vec2(greyScaleColor.r, paletteIndex);
	gl_FragColor = vec4(texture2D(palettes_texture, palette_index).rgb, greyScaleColor.a);
}
