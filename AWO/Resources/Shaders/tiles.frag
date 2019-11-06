#version 330 core

in vec2 tex_coords;
in vec4 tile_size;

out vec4 outColor;

uniform sampler2D sprite_sheet_texture;
uniform sampler2D tiles_texture;
uniform sampler2D palettes_texture;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	// Get data for this tile
	// Red/Blue: X/Y of the top-left of the tile we're drawing
	// Green: Index of the palette to apply to the grayscale value
	vec4 tile_data = texture2D(tiles_texture, tex_coords);

	vec2 bla = vec2(
		tile_data.x + tex_coords.x, 
		tile_data.y - tex_coords.y
	);


	// outColor = vec4(bla, 0.0, 1.0);
	

	outColor = texture2D(sprite_sheet_texture, bla);
	// vec4 sprite_sheet_grayscale = texture2D(sprite_sheet_texture, tile_data.rg + tex_coords);

	// outColor = sprite_sheet_grayscale;






	// Get which palette value to index into
	// float palette_row_index = tile_data.b;
	// float palette_column_index = sprite_sheet_grayscale.r;

	// Index into palette to get the final color output
	// outColor = vec4(
		// texture(palettes_texture, vec2(palette_column_index, palette_row_index)).rgb,
		// 1.0
	// );

	// Use sprite sheet grayscale pixel value to index into palette texture

	// outColor = 

	// outColor = vec4(texture(palettes_texture, sprite_sheet_grayscale).rgb, sprite_sheet_grayscale.a);


	// outColor = vec4(sprite_sheet_grayscale, sprite_sheet_grayscale, sprite_sheet_grayscale, 1.0);
	// outColor = vec4(palette_row_index, 0.0, 0.0, 1.0);

	// outColor = vec4(tile_data.rgb, 1.0);
	// outColor = texture2D(sprite_sheet_texture, tex_coords);
}
