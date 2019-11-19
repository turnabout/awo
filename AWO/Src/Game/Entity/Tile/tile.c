#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/tile.h"
#include "Game/player_index_enum.h"

Tile* create_tile(
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data, 
    Tile_Type tile_type, 
    Uint8 variation
)
{
    Tile* tile = (Tile*)malloc(sizeof(Tile));

    if (tile_type >= NEUTRAL_TILE_TYPE_FIRST && tile_type <= NEUTRAL_TILE_TYPE_LAST) {

        // Neutral tile
        tile->contents_type = Tile_Contents_Neutral;

        tile->contents = create_neutral_tile(
            tile,
            game_clock,
            tiles_data,
            tile_type,
            (Tile_Variation)variation,
            &tile->update_render_grid
        );
    } else if (tile_type >= PROPERTY_TILE_TYPE_FIRST && tile_type <= PROPERTY_TILE_TYPE_LAST) {

        // Property tile
        tile->contents_type = Tile_Contents_Property;

        tile->contents = create_property_tile(
            tile,
            game_clock,
            tiles_data,
            (Property_Type)(tile_type - PROPERTY_TILE_TYPE_FIRST),
            (Player_Index)(variation),
            &tile->update_render_grid
        );
    } else {

        // Invalid tile
        free(tile);
        return NULL;
    }

    return tile;
}

void free_tile(Tile* tile)
{
    if (tile != NULL) {
        free(tile);
    }
}