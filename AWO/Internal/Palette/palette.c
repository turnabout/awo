#include <stdlib.h>
#include <string.h>

#include "AWO/game_message.h"
#include "Palette/_palette.h"

GLuint create_game_palette_texture(
    Palette_Data* palette_data,
    Weather active_weather, 
    Army_Type player_armies[MAX_PLAYER_COUNT]
)
{
    // Create and populate the palette texture data buffer
    Palette_Data_Row* palette_buffer = malloc(sizeof(Palette_Data_Row) * PALETTE_TEX_HEIGHT);

    memset(palette_buffer, 0, sizeof(Palette_Data_Row) * PALETTE_TEX_HEIGHT);

    // Populate active tile weather palette (non-fog & then fog)
    memcpy(
        &palette_buffer[get_active_tile_palette_index_i(FALSE)],
        get_palette_data_tile_row(palette_data, active_weather, FALSE),
        sizeof(Palette_Data_Row)
    );

    memcpy(
        &palette_buffer[get_active_tile_palette_index_i(TRUE)],
        get_palette_data_tile_row(palette_data, active_weather, TRUE),
        sizeof(Palette_Data_Row)
    );

    // Populate player units & player properties palettes
    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        Army_Type player_army = player_armies[i];

        if (player_army == ARMY_TYPE_NONE) {
            continue;
        }

        // Populate player units palettes (non-done version & then done version)
        memcpy(
            &palette_buffer[get_player_unit_palette_index_i(i, FALSE)],
            get_palette_data_unit_row(palette_data, player_army, FALSE),
            sizeof(Palette_Data_Row)
        );

        memcpy(
            &palette_buffer[get_player_unit_palette_index_i(i, TRUE)],
            get_palette_data_unit_row(palette_data, player_army, TRUE),
            sizeof(Palette_Data_Row)
        );

        // Populate properties palettes
        memcpy(
            &palette_buffer[get_player_property_palette_index_i(i)],
            get_palette_data_property_row(palette_data, player_army),
            sizeof(Palette_Data_Row)
        );
    }

    // Populate neutral & fog property palettes
    memcpy(
        &palette_buffer[get_player_property_palette_index_i(Player_Index_Neutral)],
        get_palette_data_property_row(palette_data, ARMY_TYPE_NEUTRAL),
        sizeof(Palette_Data_Row)
    );

    memcpy(
        &palette_buffer[get_fog_property_palette_index_i()],
        get_palette_data_fog_property_row(palette_data),
        sizeof(Palette_Data_Row)
    );

    // Create texture from the populated palette buffer
    GLuint palette_texture = create_texture_object(
        (Uint8*)palette_buffer,
        PALETTE_TEX_WIDTH,
        PALETTE_TEX_HEIGHT,
        4
    );

    free(palette_buffer);

    // Before exiting, apply the initial weather colors to the properties palettes
    update_properties_weather_colors(palette_texture);

    return palette_texture;
}
