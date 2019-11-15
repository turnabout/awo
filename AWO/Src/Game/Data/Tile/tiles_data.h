#pragma once

#include <cJSON.h>

#include "types.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/enums.h"

/*! @brief Holds all of the game's data for regular tiles.
 */
typedef struct Tiles_Data Tiles_Data;

/*! @brief Creates the tiles data object.
 *
 *  @param[in] tiles_data_JSON The JSON describing the tiles' data.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The generated tiles data object.
 */
Tiles_Data* create_tiles_data(cJSON* tiles_data_JSON, int ss_width, int ss_height);

/*! @brief Gets whether the given tile/variation combination exists in tiles data.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] type The tile type to check.
 *  @param[in] var The tile variation to check.
 *  @return TRUE if it exists, FALSE if it doesn't.
 */
Bool tile_type_variation_exists(Tiles_Data* tiles_data, Tile_Type type, Tile_Variation var);

/*! @brief Gets the tile variation the given middle tile should have, according to the given 
 *  adjacent tiles.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] middle_tile The middle tile surrounded by the other given tiles.
 *  @param[in] top_tile The top adjacent tile.
 *  @param[in] right_tile The right adjacent tile.
 *  @param[in] bottom_tile The bottom adjacent tile.
 *  @param[in] left_tile The left adjacent tile.
 *  @return The generated auto tile_var.
 */
Tile_Variation get_tile_auto_var(
    Tiles_Data* tiles_data,
    Tile_Type middle_tile,
    Tile_Type top_tile,
    Tile_Type right_tile,
    Tile_Type bottom_tile,
    Tile_Type left_tile
);

/*! @brief Gathers data on tile of given type & variation.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] type The tile's type.
 *  @param[in] variation The tile variation.
 *  @param[out] clock_index Filled with the tile's animation clock index.
 *  @param[out] sub_clock_index Filled with the tile's sub-clock index.
 *  @param[out] animation Filled with the tile's Animation object.
 */
void gather_tile_data(
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation var,
    Animation_Clock_Index* clock,
    Animation_Sub_Clock_Index* sub_clock,
    Animation** animation
);

/*! @brief Gets the next tile variation belonging to the given tile type.
 *  Must be called continuously until it returns NULL.
 *  Goes through all tile variations of the tile type until all have been returned.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] type The tile's type.
 *  @return The next tile variation belonging to this tile type or TILE_VAR_NONE if the tile
 *          type has no more variation.
 */
Tile_Variation get_next_tile_type_var(Tiles_Data* tiles_data, Tile_Type type);

/*! @brief Gets the next tile variation animation for the given tile type.
 *  Must be called continuously until it returns NULL.
 *  Goes through all tile variations of the tile type until all have been returned.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] type The tile's type.
 *  @return The next tile's Animation object or NULL if the tile has no more animation.
 */
Animation* get_next_tile_type_var_animation(Tiles_Data* tiles_data, Tile_Type type);

/*! @brief Gets the first (default) tile variation for a tile type.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] type The tile's type.
 *  @return The default tile variation for the given tile type.
 */
Tile_Variation get_tile_type_default_var(Tiles_Data* tiles_data, Tile_Type type);

/*! @brief Frees all memory occupied by tiles data.
 *
 *  @param[in] tiles_data The tiles data object.
 */
void free_tiles_data(Tiles_Data* tiles_data);

#ifdef _DEBUG
/*! @brief Prints all contents stored in tiles data.
 *
 *  @param[in] tiles_data The tiles data object.
 */
void print_tiles_data(Tiles_Data* tiles_data);
#endif
