#version 330 core

in vec2 tex_coords;

out vec4 outColor;

uniform sampler2D sprite_sheet_texture;
uniform sampler2D tiles_texture;
uniform sampler2D palettes_texture;

// Base size of a regular tile, in pixels
float base_tile_size = 16.0;

// TODO: make into a uniform
// Tilemap quad dimensions in pixels
float quad_width = 640.0;
float quad_height = 640.0;

// TODO: make into a uniform
// Sprite sheet dimensions in pixels
float sprite_sheet_width = 456.0;
float sprite_sheet_height = 454.0;

void main()
{
	// 1. Get data for this tile
	// Red/Blue: X/Y of the top-left of the tile we're drawing, in pixels
	// Green: Index of the palette to apply to the grayscale value
	vec4 tile_data = texture2D(tiles_texture, tex_coords);

	// 2. Get the sprite sheet grayscale value
	// Take the tile's top-left coordinates & add current quad texture offset coordinates
	// along with offset to get the correct sprite sheet coordinates
	vec2 tex_coords_offset;

	vec2 sprite_sheet_coordinates = vec2(
		(tile_data.x * 510.0) / sprite_sheet_width + ( 
			mod( (tex_coords.x * quad_width), base_tile_size ) / sprite_sheet_width
		),
		(tile_data.y * 510.0) / sprite_sheet_height + ( 
			mod( (tex_coords.y * quad_height), base_tile_size ) / sprite_sheet_height
		)
	);

	vec4 sprite_sheet_grayscale = texture2D(sprite_sheet_texture, sprite_sheet_coordinates);

	// 3. Get palette indexing values

	float palette_row_index = tile_data.b;
	float palette_column_index = sprite_sheet_grayscale.r;

	// 4. Index into textures palette to get the final color output
	outColor = vec4(
		texture(palettes_texture, vec2(palette_column_index, palette_row_index)).rgb,
		sprite_sheet_grayscale.a
	);

	// outColor = sprite_sheet_grayscale;
	// outColor = vec4(tile_data.x, tile_data.y, 0.0, 1.0);
}
