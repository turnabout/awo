#pragma once

#include "Game/Editor/game_editor.h"

// Selected entity type/variation set as this value when unset
#define SELECTED_ENTITY_TYPE_NONE -1
#define SELECTED_ENTITY_VAR_NONE -1

// Entity coordinates set as this value when unset
#define ENTITY_COORDINATE_NONE -1

/*! @brief Callback used by the game editor to edit an entity.
 */
typedef void (*Editor_Set_Cb)(Game_Editor*, Game_Board*, Game_Clock*);

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
    Editor_Set_Cb selected_entity_update_cb;

    // References to tiles & units data
    Tiles_Data* tiles_data;
    Units_Data* units_data;

    // Placement rules for the currently-selected (neutral) tile.
    Tile_Placement_Rule_Set* placement_rules;

    // Game board coordinates currently hovered.
    int hovered_x, hovered_y;

    // Whether the currently selected entity can be placed at the currently hovered coordinates
    Bool entity_placeable;

    // UI box showing the currently selected entity
    // Selected_Entity* selected_entity;
};

void set_editor_unit_entity(Game_Editor* editor, Game_Board* board, Game_Clock* clock);
void set_editor_tile_entity(Game_Editor* editor, Game_Board* board, Game_Clock* clock);

void set_editor_property_entity(Game_Editor* editor, Game_Board* board, Game_Clock* clock);

/*! @brief Apply auto-var to the tile entity at the given x/y coordinates.
 */
void apply_autovar(Game_Editor* editor, Game_Board* board, Game_Clock* clock, Uint8 x, Uint8 y);

/*! @brief Checks whether the tile placement rules pass at the given game board coordinates.
 */
Bool is_editor_tile_placeable(
    Tile_Placement_Rule_Set* rule_set,
    Game_Board* game_board,
    int x,
    int y
);
