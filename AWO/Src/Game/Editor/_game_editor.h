#pragma once

#include "Game/Editor/game_editor.h"

/*! @brief Callback used by the game editor to edit an entity.
 */
typedef void (*Editor_Update_Cb)(Game_Editor* editor);

/*! @brief Every possible mode for the game editor.
 */
typedef enum Game_Editor_Mode {
    Editor_Mode_Neutral,
    Editor_Mode_Dragging,
} Game_Editor_Mode;

/*! @brief The game editor module. Edits entities in the game board in design room mode according
 *  to user input.
 */
struct Game_Editor {

    // Coordinates of the entity we're currently editing (and previously did)
    int entity_x, entity_y;

    // Currently selected tile type & variation
    int selected_entity_type, selected_entity_var;

    // Current mode
    Game_Editor_Mode mode;

    // Current callback function used to update entities
    Editor_Update_Cb update_cb;

    // UI box showing the currently selected entity
    // Selected_Entity* selected_entity;
};

void update_unit_entity(Game_Editor* editor);
void update_neutral_tile_entity(Game_Editor* editor);
void update_property_tile_entity(Game_Editor* editor);

/*! @brief Apply auto-var to the tile entity at the given x/y coordinates.
 */
void apply_autovar(Game_Editor* editor, Uint8 x, Uint8 y);