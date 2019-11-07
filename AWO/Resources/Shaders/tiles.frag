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
	// 1. Get data for this tile
	// Red/Blue: X/Y of the top-left of the tile we're drawing
	// Green: Index of the palette to apply to the grayscale value
	vec4 tile_data = texture2D(tiles_texture, tex_coords);

	// 2. Get the sprite sheet grayscale value
	// Take the tile's top-left coordinates & add current quad offset coordinates, converted
	// to the sprite sheet's size, to it to get the correct sprite sheet coordinates
	vec2 sprite_sheet_coordinates = vec2(
		tile_data.x + ((tex_coords.x * 640) / 628),
		tile_data.y + ((tex_coords.y * 640) / 396)
	);

	vec4 sprite_sheet_grayscale = texture2D(sprite_sheet_texture, sprite_sheet_coordinates);

	// 3. Get palette indexing values

	float palette_row_index = tile_data.b;
	float palette_column_index = sprite_sheet_grayscale.r;

	// 4. Index into textures palette to get the final color output
	outColor = vec4(
		texture(palettes_texture, vec2(palette_column_index, palette_row_index)).rgb,
		1.0
	);
}
