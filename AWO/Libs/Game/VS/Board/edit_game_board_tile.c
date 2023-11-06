#include "Game/Board/_game_board.h"
#include "Game/Entity/Tile/tile.h"

void edit_game_board_neutral_tile(
    Neutral_Tile* tile,
    Game_Board* game_board,
    Clock* game_clock,
    Tile_Variation new_variation
)
{
    // Don't bother editing if the new variation is same as old one
    if (tile->variation == new_variation) {
        return;
    }

    edit_neutral_tile_variation(tile, game_clock, game_board->tiles_data, new_variation);
    tile->update_grid(game_board->game_renderer, (void*)tile, 0);
}

void edit_game_board_property_tile(
    Property_Tile* property,
    Game_Board* game_board,
    Player_Index new_index
)
{
    // Don't bother editing if the new index is same as old one
    if (property->player->index == new_index) {
        return;
    }

    // Unregister the property with its old player's list
    unregister_game_board_player_property(game_board, property);

    // Update the property's player index & register it with its new player owner's list
    update_property_owner(property, game_board->tiles_data, game_board->players[new_index]);
    property->update_palette(game_board->game_renderer, (void*)property, 0);
    property->update_grid(game_board->game_renderer, (void*)property, 0);
    register_game_board_player_property(game_board, property);
}

void edit_game_board_tile(
    Game_Board* game_board,
    Clock* game_clock,
    Tile_Type new_type,
    int new_variation,
    Uint8 x,
    Uint8 y
)
{
    Tile* tile = game_board->tiles_grid[y][x];

    // Same tile type, edit the tile itself rather than delete and replace it
    if (tile->type == new_type) {
        if (tile->type >= NEUTRAL_TILE_TYPE_FIRST && tile->type <= NEUTRAL_TILE_TYPE_LAST) {
            edit_game_board_neutral_tile(
                (Neutral_Tile*)tile,
                game_board,
                game_clock,
                (Tile_Variation)new_variation
            );

        } else {
            edit_game_board_property_tile(
                (Property_Tile*)tile,
                game_board,
                (Player_Index)new_variation
            );
        }

        return;
    }

    // If the old tile to delete is a property, unregister it from its player's list
    if (tile->type >= PROPERTY_TILE_TYPE_FIRST && tile->type <= PROPERTY_TILE_TYPE_LAST) {
        unregister_game_board_player_property(game_board, (Property_Tile*)tile);
    }

    // New tile type, delete the old tile and replace with a new one
    tile->delete(game_board->game_renderer, game_clock, (void*)tile, (void*)game_board->tiles_data);

    add_game_board_tile(
        game_board,
        game_clock,
        new_type,
        new_variation,
        x,
        y
    );
}
