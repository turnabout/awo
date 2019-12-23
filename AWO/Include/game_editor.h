#pragma once

#include "game.h"
#include "game_data.h"

/*! @brief Every possible entity type the game editor can edit.
 */
typedef enum Game_Editor_Entity_Type {
    Editor_Entity_Type_Tile,
    Editor_Entity_Type_Unit,
} Game_Editor_Entity_Kind;

/*! @brief Updates the game editor's selected entity.
 *
 *  @param[in] game The game object.
 *  @param[in] kind
 *  @param[in] type
 *  @param[in] variation
 */
void update_game_editor_selected_entity(
    Game* game,
    Game_Editor_Entity_Kind kind,
    int type,
    int variation
);
