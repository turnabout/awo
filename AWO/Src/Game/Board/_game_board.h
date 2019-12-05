#pragma once

#include "Game/Board/game_board.h"
#include "Game/Entity/Tile/Property_Tile/property_tile.h"
#include "Utilities/Linked_List/linked_list.h"

typedef Tile** Tile_Row;

struct Game_Board {

    // Contains all tiles on the game board. tiles[board_y][board_x]
    Tile_Row* tiles_grid;

    // Descriptor of the loaded stage.
    Stage* stage;

    Player* players[MAX_PLAYER_COUNT + 1];

    // How many actual players (excluding 'neutral') are playing.
    Uint8 player_count;

    // Lists of properties belonging to each player. ( + 1 for neutral player )
    Linked_List* player_properties[MAX_PLAYER_COUNT + 1];

};

/*! @brief Loads stage described by the given stage descriptor into the game board.
 *
 *  @param[in] game_board The game board.
 *  @param[in] game_clock The game clock object.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] stage_descriptor Descriptor detailing the stage to load.
 */
void load_game_board_stage(
    Game_Board* game_board, 
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Stage* stage_descriptor
);

/*! @brief Adds a new tile of the given type and variation to the game board at x/y coordinate.
 *
 *  @param[in] game_board The game board.
 *  @param[in] game_clock The game clock.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] tile_type Type of the tile to add.
 *  @param[in] variation Variation of the newly added tile.
 *  @param[in] x Game board x coordinate of the new tile.
 *  @param[in] y Game board y coordinate of the new tile.
 */
void add_game_board_tile(
    Game_Board* game_board,
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    int tile_variation,
    Uint8 x,
    Uint8 y
);

/*! @brief Registers a property with a player.
 *
 *  @param[in] game_board The game board module.
 *  @param[in] property Pointer to the property to register.
 */
void register_game_board_player_property(Game_Board* game_board, Property_Tile* property);

/*! @brief Unregisters a property with a player.
 *
 *  @param[in] game_board The game board module.
 *  @param[in] property Pointer to the property to unregister.
 */
void unregister_game_board_player_property(Game_Board* game_board, Property_Tile* property);
