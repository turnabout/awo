#include "Utilities/Message_Service/message_service.h"
#include "Game/Editor/_game_editor.h"

Bool is_editor_tile_placeable(
    Tile_Placement_Rule_Set* rule_set, 
    Game_Board* game_board, 
    int x, 
    int y
)
{
    // If OOB, false result right away
    if (x == -1 || y == -1) {
        return FALSE;
    }

    // If no rule set, tile should be placeable no matter what
    if (rule_set == NULL) {
        return TRUE;
    }

    // Check the rule set by looping every rule
    for (Uint8 i = 0; i < rule_set->rule_count; i++) {

        // Keep track of this rule's components passing
        Bool rule_ok = FALSE;

        // Loop every component for this rule
        for (Uint8 j = 0; j < rule_set->rules[i]->component_count; j++) {
            Tile_Placement_Rule_Component* component = &rule_set->rules[i]->components[j];

            // Get tile type of the component's tile offset to check
            Tile_Type component_checked_tile = get_game_board_tile_type(
                game_board,
                x + component->offset_x,
                y + component->offset_y
            );

            // Check whether the tile is one of this rule component's blocked tiles.
            // As soon as one of the rule components evaluate to false, this rule is OK.
            if (!(1 << component_checked_tile & component->blocked_tiles)) {
                rule_ok = TRUE;
                break;
            }
        }

        // If all of the rule components evaluate to true, the tile is not placeable
        if (!rule_ok) {
            printw("Rule index %d blocked", i);

            return FALSE;
        }
    }

    return TRUE;
}
