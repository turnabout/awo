#pragma once

// Internal
#include "../Config/config.h"
#include "../Utilities//utilities.h"
#include "../Player/player_index_enum.h"

// Libs
#include "../../Libs/Game_Data/game_data.h"

#define STAGE_NAME_MAX_LENGTH 32

/*! @brief Describes the contents of a tile within a level.
 */
typedef struct Stage_Tile {

    // Type of the tile.
    Tile_Type type;

    // Variation of the tile.
    // For a neutral tile: tile variation.
    // For a property tile: owner player's index.
    int variation;

} Stage_Tile;

/*! @brief A row of stage tiles.
 */
typedef Stage_Tile* Stage_Tile_Row;

/*! @brief Describes the contents of a stage, which can be loaded by the game board for gameplay.
 */
typedef struct Stage {

    // The name of the stage.
    char name[STAGE_NAME_MAX_LENGTH];

    // The dimensions of the stage.
    Uint8 width, height;

    // Descriptors of every tile making up the stage.
    Stage_Tile_Row* tiles_grid;

    // Amount of players on this stage.
    Uint8 player_count;

    // Array containing the army of each player.
    Army_Type player_armies[MAX_PLAYER_COUNT];

} Stage;

/*! @brief Loads a stage using the given stage string.
 *
 *  @param[in] stage_str String describing the stage.
 *  @param[in] tiles_data The tiles data object. Used to validate tiles.
 *  @return The created stage, or NULL if the stage string was invalid.
 */
Stage* generate_stage_from_string(char* stage_str, Tile_Data* tiles_data);

/*! @brief Validates a stage is OK to play on (OK player count, property count, etc).
 *
 *  @param[in] stage The stage to validate.
 *  @return Whether the stage validation passed.
 */
Bool validate_stage(Stage* stage);

/*! @brief Stringifies the given stage into a string that can later be loaded.
 *  @param[in] stage Stage to transform into a string.
 *  @return The generated string. NULL if the stage is not valid.
 */
char* stringify_stage(Stage* stage);

/*! @brief Generates a stage filled up with tiles of the given type and variation.
 *
 *  @param[in] type The type of the tile used to fill the stage width.
 *  @param[in] variation The variation of the tile used to fill the stage width.
 *  @param[in] width The width of the generated stage.
 *  @param[in] height The height of the generated stage.
 *  @return The generated stage.
 */
Stage* generate_filled_stage(
    Tile_Type type,
    Tile_Variation variation,
    Uint8 width,
    Uint8 height
);

/*! @brief Generate a custom, hardcoded stage for debug purposes.
 *  @return The generated stage.
 */
Stage* generate_custom_stage();

/*! @brief Edits the values of a stage tile.
 *
 *  @param[in] stage The stage.
 *  @param[in] x The X coordinate of the stage tile to edit.
 *  @param[in] y The Y coordinate of the stage tile to edit.
 *  @param[in] type The stage tile's new type.
 *  @param[in] variation The stage tile's new variation.
 */
void edit_stage_tile(Stage* stage, int x, int y, int type, int variation);

/*! @brief Gets the army type of a stage's player index.
 *
 *  @param[in] stage The stage.
 *  @param[in] index The player index from which to get the army type.
 *  @return The army type of the player of the given index.
 */
Army_Type get_stage_player_index_army_type(Stage* stage, Player_Index index);

/*! @brief Frees data taken up by a stage descriptor.
 *
 *  @param[in] stage_descriptor The stage descriptor.
 */
void free_stage(Stage* stage_descriptor);