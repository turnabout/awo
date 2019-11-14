#pragma once

#include "types.h"
#include "Game/Data/Tile/tiles_data.h"

#define STAGE_STRING_SEPARATOR_CHARACTER 0xFF
#define STAGE_NAME_MIN_LENGTH              4
#define STAGE_NAME_MAX_LENGTH             16

#define STAGE_MAX_WIDTH                  255
#define STAGE_MAX_HEIGHT                 255
#define STAGE_MIN_SURFACE                 10

/*! @brief Confirms the given stage data is valid and usable for a game.
 *
 *  @param[in] stage_data The stage data bytes array.
 *  @param[in] data_length The length of the stage data.
 *  @param[in] tiles_data The tiles data object. Used to validate tiles.
 *  @return TRUE if the data is valid, FALSE if invalid.
 */
Bool validate_stage_data(Uint8* stage_data, size_t data_length, Tiles_Data* tiles_data);
