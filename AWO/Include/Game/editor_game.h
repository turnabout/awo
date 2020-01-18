#pragma once

#include "../Game_Data/game_data.h"
#include "../Game_Window/game_window.h"
#include "game.h"

/*! @brief Game in editor mode. Edit a stage and export it as a string.
 */
typedef struct Editor_Game Editor_Game;

/*! @brief Every possible entity type the game editor can edit.
 */
typedef enum Game_Editor_Entity_Type {
    Editor_Entity_Type_Tile,
    Editor_Entity_Type_Unit,
} Game_Editor_Entity_Kind;

Game* create_editor_game(Game_Data* game_data, Game_Window* game_window);

void free_editor_game(Game* game);

/*! @brief Updates the game editor's selected entity.
 *
 *  @param[in] game The game object.
 *  @param[in] kind
 *  @param[in] type
 *  @param[in] variation
 */
/*
void update_game_editor_selected_entity(
    Game* game,
    Game_Editor_Entity_Kind kind,
    int type,
    int variation
);
*/
