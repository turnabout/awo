#include "Game/Entity/Tile/tile.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Data/Palette/game_palette.h"

void update_regular_property_fog_status(Tile* tile, Bool fog)
{
    GLfloat palette_index = fog 
        ? get_fog_property_palette_index() 
        : get_player_property_palette_index(((Property_Tile*)tile)->player->army);

    update_tile_layer_pixel_high( TILE_LAYER_0, tile->x, tile->y, (vec2) { palette_index, 0.0f } );
    update_tile_layer_pixel_high( TILE_LAYER_1, tile->x, tile->y, (vec2) { palette_index, 0.0f } );
}

void update_base_fog_status(Tile* tile, Bool fog)
{
    // TODO
}
