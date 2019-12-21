#pragma once

#include "Game/Editor/game_editor.h"

/*! @brief Callback used by the game editor to edit an entity.
 */
typedef void (*EditorUpdateCb)();

/*! @brief Every possible mode for the game editor.
 */
typedef enum Game_Editor_Mode {
    GAME_EDITOR_MODE_NEUTRAL,
    GAME_EDITOR_MODE_DRAGGING,
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

    // UI box showing the currently selected entity
    // Selected_Entity* selected_entity;
};