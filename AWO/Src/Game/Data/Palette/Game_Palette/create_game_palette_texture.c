#include <stdlib.h>
#include <string.h>

#include "Game/Data/Palette/_palette.h"

GLuint create_game_palette_texture(
    GLuint raw_palette_texture, 
    Weather active_weather, 
    Army_Type player_armies[MAX_PLAYER_COUNT]
)
{
    // Get the raw palette texture data
    Palette_Texture_Row* raw_palette_texture_data = (Palette_Texture_Row*)malloc(
        sizeof(Palette_Texture_Row) * PALETTE_TEX_HEIGHT
    );

    glBindTexture(GL_TEXTURE_2D, raw_palette_texture);

    glGetTexImage(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        raw_palette_texture_data
    );

    // Create and populate destination the game palette texture data
    Palette_Texture_Row* game_palette_texture_data = (Palette_Texture_Row*)malloc(
        sizeof(Palette_Texture_Row) * PALETTE_TEX_HEIGHT
    );

    // Get the size of a single row in a palette texture
    // * 4 due to an RGBA array taking up 4 bytes
    size_t row_size = 4 * PALETTE_TEX_WIDTH;

    // Populate active tile palette
    // printf("%d -> %d\n", get_tile_palette_index_i(active_weather, 0), get_active_tile_palette_index_i(0));
    // printf("%d -> %d\n", get_tile_palette_index_i(active_weather, 1), get_active_tile_palette_index_i(1));

    memcpy(
        &game_palette_texture_data[get_active_tile_palette_index_i(0)],
        &raw_palette_texture_data[get_tile_palette_index_i(active_weather, 0)],
        row_size
    );

    memcpy(
        &game_palette_texture_data[get_active_tile_palette_index_i(1)],
        &raw_palette_texture_data[get_tile_palette_index_i(active_weather, 1)],
        row_size
    );

    // Populate player units & player properties palettes
    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        Army_Type player_army = player_armies[i];

        if (player_army == ARMY_TYPE_NONE) {
            continue;
        }

        // Populate player units palettes
        // printf("%d -> %d\n",get_unit_palette_index_i(player_army, 0) ,get_player_unit_palette_index_i(i, 0));
        // printf("%d -> %d\n",get_unit_palette_index_i(player_army, 1) ,get_player_unit_palette_index_i(i, 1));
        // printf("%d -> %d\n", get_player_property_palette_index_i(i), get_player_property_palette_index_i(i));

        memcpy(
            &game_palette_texture_data[get_player_unit_palette_index_i(i, 0)],
            &raw_palette_texture_data[get_unit_palette_index_i(player_army, 0)],
            row_size
        );

        memcpy(
            &game_palette_texture_data[get_player_unit_palette_index_i(i, 1)],
            &raw_palette_texture_data[get_unit_palette_index_i(player_army, 1)],
            row_size
        );

        // Populate properties palettes
        memcpy(
            &game_palette_texture_data[get_player_property_palette_index_i(i)],
            &raw_palette_texture_data[get_property_palette_index_i(player_army)],
            row_size
        );
    }

    // Populate neutral & fog property palettes
    // printf("%d -> %d\n", get_property_palette_index_i(UNIT_VAR_NEUTRAL), get_player_property_palette_index_i(Player_Index_Neutral));
    // printf("%d -> %d\n", get_raw_fog_property_palette_index_i(), get_fog_property_palette_index_i());
    memcpy(
        &game_palette_texture_data[get_player_property_palette_index_i(Player_Index_Neutral)],
        &raw_palette_texture_data[get_property_palette_index_i(ARMY_TYPE_NEUTRAL)],
        row_size
    );

    memcpy(
        &game_palette_texture_data[ get_fog_property_palette_index_i()],
        &raw_palette_texture_data[get_raw_fog_property_palette_index_i()],
        row_size
    );

    // Create the texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        PALETTE_TEX_WIDTH, 
        PALETTE_TEX_HEIGHT, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        game_palette_texture_data
    );

    free(game_palette_texture_data);
    free(raw_palette_texture_data);

    return texture;
}
