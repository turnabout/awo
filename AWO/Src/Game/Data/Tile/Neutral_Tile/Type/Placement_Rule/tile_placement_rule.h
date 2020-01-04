#pragma once

#include <cJSON.h>

#include "types.h"

typedef struct Tile_Placement_Rule_Component {

    // The X offset of the tile this component applies to.
    Uint8 offset_x;

    // The Y offset of the tile this component applies to.
    Uint8 offset_y;

    // Bit-field representing the tile types that are blocked by this rule.
    Uint32 blocked_tiles;

} Tile_Placement_Rule_Component;

typedef struct Tile_Placement_Rule {

    // Amount of components making up this rule.
    Uint8 components_count;

    // Array of components making up this rule.
    Tile_Placement_Rule_Component* components;

} Tile_Placement_Rule;

/*! @brief Creates a tile placement rule.
 *
 *  @param[in] JSON The JSON object representing this tile placement rule.
 *  @return The allocated tile placement rule.
 */
Tile_Placement_Rule* create_tile_placement_rule(cJSON* JSON);

/*! @brief Frees an allocated tile placement rule.
 *
 *  @param[in] rule The rule to free.
 */
void free_tile_placement_rule(Tile_Placement_Rule* rule);
