#pragma once

#include <cJSON.h>

#include "Utilities/utilities.h"

typedef struct Tile_Placement_Rule_Component {

    // The X offset of the tile this component applies to.
    Sint8 offset_x;

    // The Y offset of the tile this component applies to.
    Sint8 offset_y;

    // Bit-field representing the tile types that are blocked by this rule.
    Uint32 blocked_tiles;

} Tile_Placement_Rule_Component;

typedef struct Tile_Placement_Rule {

    // Amount of components making up this rule.
    Uint8 component_count;

    // Array of components making up this rule.
    Tile_Placement_Rule_Component* components;

} Tile_Placement_Rule;

/*! @brief An array of tile placement rules.
 */
typedef struct Tile_Placement_Rule_Set {

    // Amount of components making up this rule.
    Uint8 rule_count;

    // Array of components making up this rule.
    Tile_Placement_Rule** rules;

} Tile_Placement_Rule_Set;

/*! @brief Creates a set of tile placement rules.
 *
 *  @param[in] JSON The JSON object representing this tile placement rule set.
 *  @return The allocated tile placement rule set.
 */
Tile_Placement_Rule_Set* create_tile_placement_rule_set(cJSON* JSON);

/*! @brief Frees a set of tile placement rules.
 *
 *  @param[in] rule_set The rule set to free.
 */
void free_tile_placement_rule_set(Tile_Placement_Rule_Set* rule_set);
