#version 100

precision mediump float;

varying vec2 texCoords;

uniform sampler2D sprite_sheet;

void main()
{
	// Get greyscale color from raw texture
	// vec4 greyScaleColor = texture2D(sprite_sheet, texCoords);

	// Index into palette
	// vec2 palette_index = vec2(greyScaleColor.r, paletteIndex);
	gl_FragColor = texture2D(sprite_sheet, texCoords);
}
