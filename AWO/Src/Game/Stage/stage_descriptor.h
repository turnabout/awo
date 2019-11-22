#pragma once

#include "types.h"
#include "conf.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Unit/units_data.h"
#include "Game/Stage/stage_descriptor.h"

#define STAGE_NAME_MAX_LENGTH 16

/*! @brief Describes the contents of a tile within a level.
 */
typedef struct Tile_Descriptor {

    // Type of the tile.
    Tile_Type type;

    // Variation of the tile.
    // For a neutral tile: tile variation.
    // For a property tile: owner player's index.
    int variation;

} Tile_Descriptor;

/*! @brief Describes the contents of a level, which can be loaded by the game board for gameplay.
 */
typedef struct Stage_Descriptor {

    // The name of the stage.
    char name[STAGE_NAME_MAX_LENGTH];

    // The dimensions of the stage.
    Uint8 width, height;

    // How many tiles are present in the stage.
    Uint16 tiles_amount;

    // Descriptors of every tile making up the stage.
    Tile_Descriptor* tile_descriptors;

    // Amount of players on this stage.
    Uint8 player_count;

    // Array containing the army of each player.
    Army_Type player_armies[MAX_PLAYER_COUNT];

}Stage_Descriptor;

/*! @brief Loads a stage descriptor using the given stage string.
 *
 *  @param[in] stage_str String describing the stage.
 *  @param[in] tiles_data The tiles data object. Used to validate tiles.
 *  @return The created stage descriptor instance, or NULL if the stage string was invalid.
 */
Stage_Descriptor* load_stage_descriptor(char* stage_str, Tiles_Data* tiles_data);

/*! @brief Frees data taken up by a stage descriptor.
 *
 *  @param[in] stage_descriptor The stage descriptor.
 */
void free_stage_descriptor(Stage_Descriptor* stage_descriptor);