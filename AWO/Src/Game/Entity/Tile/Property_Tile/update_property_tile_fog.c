#include "Game/Entity/Tile/tile.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Data/Palette/game_palette.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_grid.h"

void update_regular_property_fog_status(void* tile, Bool fog)
{
    GLfloat palette_index = fog 
        ? get_fog_property_palette_index() 
        : get_player_property_palette_index(((Property_Tile*)tile)->player->index);

    update_tile_layer_pixel_high( 
        TILE_LAYER_0, 
        ((Tile*)tile)->x, 
        ((Tile*)tile)->y, 
        (vec2) { palette_index, 0.0f } 
    );

    update_tile_layer_pixel_high( 
        TILE_LAYER_1, 
        ((Tile*)tile)->x, 
        ((Tile*)tile)->y, 
        (vec2) { palette_index, 0.0f } 
    );
}

void update_base_fog_status(void* tile, Bool fog)
{
    GLfloat palette_index;

    if (fog) {
        palette_index = get_fog_property_palette_index();

        // If fog, switch to using the regular property render grid CB so base smoke doesn't show
        ((Property_Tile*)tile)->update_render_grid = update_regular_property_render_grid;

    } else {
        palette_index = get_player_property_palette_index(((Property_Tile*)tile)->player->index);

        // If no fog AND base player index is not neutral, switch to using the base-specific render 
        // grid CB so base smoke shows
        if (((Property_Tile*)tile)->player->index != Player_Index_Neutral) {
            ((Property_Tile*)tile)->update_render_grid = update_base_render_grid;
        } else {
            ((Property_Tile*)tile)->update_render_grid = update_regular_property_render_grid;
        }
    }

    update_tile_layer_pixel_high( 
        TILE_LAYER_0, 
        ((Tile*)tile)->x, 
        ((Tile*)tile)->y, 
        (vec2) { palette_index, 0.0f } 
    );

    update_tile_layer_pixel_high( 
        TILE_LAYER_1, 
        ((Tile*)tile)->x, 
        ((Tile*)tile)->y, 
        (vec2) { palette_index, 0.0f } 
    );
}
