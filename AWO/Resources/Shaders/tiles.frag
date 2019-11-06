#version 330 core

in vec2 texCoords;

out vec4 outColor;

uniform sampler2D sprite_sheet;
uniform sampler2D tiles_texture;
uniform sampler2D palettes_texture;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	// Get greyscale color from raw texture
	// vec4 greyScaleColor = texture(sprite_sheet, vec2(0.0, 0.5));

	// vec4 tiles_data = texture(tiles_texture, texCoords);

	// vec4 greyScaleColor = texture(sprite_sheet, texCoords);
	// vec2 palette_index = vec2(greyScaleColor.r, 0.0);

	// Index into palette
	// outColor = vec4(texture(palettes_texture, palette_index).rgb, greyScaleColor.a);

	// outColor = tiles_data;

	// outColor = texture(tiles_texture, texCoords);

	// outColor = texture(palettes_texture, texCoords);
	// outColor = vec4(1.0, 1.0, 1.0, 1.0);

	vec4 tile = texture2D(tiles_texture, texCoords);

	// tile.b = 1.0;

	// outColor = tile;

	vec4 pos_result =  projection *  vec4(gl_FragCoord.xy, 0.0, 1.0);

	outColor = vec4(pos_result.xyz, 1.0);
}
