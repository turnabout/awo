#include "tile_types.h"
#include "tile_variations.h"

/*! @brief Holds all of the game's data for regular tiles.
 */
typedef struct Tile_Data Tile_Data;

/*! @brief Gets the next tile variation for a neutral tile type.
 *
 *  @note Must be called continuously until it returns NULL.
 *
 *  @param[in] tile_data The tile data module.
 *  @param[in] type The type from which to get the next variation.
 *  @return The tile variation, or TILE_VAR_NONE if the given type has no more variations.
 */
Tile_Variation get_next_game_tile_var(Tile_Data tile_data, Tile_Type type);
