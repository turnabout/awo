#pragma once

#include "types.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Stage/stage_descriptor.h"

#define STAGE_NAME_MAX_LENGTH 16

typedef struct Tile_Descriptor {
    Tile_Type type;
    Tile_Variation variation;
} Tile_Descriptor;

typedef struct Stage_Descriptor {

    // The name of the stage.
    char name[STAGE_NAME_MAX_LENGTH];

    // The dimensions of the stage.
    Uint8 width, height;

    // How many tiles are present in the stage.
    Uint16 tiles_amount;

    // Descriptors of every tile making up the stage.
    Tile_Descriptor* tile_descriptors;

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