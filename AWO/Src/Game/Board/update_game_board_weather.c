#include "Game/Data/Palette/game_palette.h"
#include "Game/Board/_game_board.h"

void re_render_player_properties(void* property, void* game_renderer)
{
    ((Property_Tile*)property)->update_render_grid((Game_Renderer*)game_renderer, property, 0);
}

void update_game_board_weather(Game_Board* game_board, Weather weather)
{
    if (weather == game_board->weather) {
        return;
    }

    // Update the palette used by tiles
    update_active_tile_palette(
        weather, 
        game_board->game_palette_texture, 
        game_board->raw_palette_texture
    );

    // Update property tiles' weather variation
    // Only necessary if going "Clear/Rain -> Snow" or "Snow -> Clear/Rain"
    if (weather == Snow || game_board->weather == Snow) {
        update_tiles_data_active_property_weather_var(game_board->tiles_data, weather);

        // Re-render all properties with their updated frame data
        for (int i = 0; i < game_board->stage->player_count; i++) {
            loop_linked_list(
                game_board->player_properties[i], 
                re_render_player_properties, 
                (void*)game_board->game_renderer
            );
        }

        loop_linked_list(game_board->player_properties[Player_Index_Neutral], re_render_player_properties, NULL);
    }

    game_board->weather = weather;
}
