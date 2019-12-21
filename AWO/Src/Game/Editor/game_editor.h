#pragma once

#include "Game/Board/game_board.h"
#include "Game/Clock/game_clock.h"
#include "Game/Camera/game_camera.h"
#include "Game/Inputs/Mouse/mouse.h"

/*! @brief Every possible entity type the game editor can edit.
 */
typedef enum Game_Editor_Entity_Type {
    Editor_Entity_Type_Tile,
    Editor_Entity_Type_Unit,
} Game_Editor_Entity_Type;

/*! @brief The game editor module. Edits entities in the game board in design room mode according
 *  to user input.
 */
typedef struct Game_Editor Game_Editor;

/*! @brief Creates the game editor module.
 *
 * @note Used in "design room" game mode to fully edit the stage currently loaded by the game 
 * board.
 *
 *  @param[in] window_width Pointer to the game window's width.
 *  @param[in] window_height Pointer to the game window's height.
 *  @return The created game editor module.
 */
Game_Editor* create_game_editor(int* window_width, int* window_height);

/*! @brief Updates the entity type currently being edited by the game editor.
 *
 *  @param[in] editor The game editor module.
 *  @param[in] new_type The new type of entity the module should edit.
 */
void update_editor_entity_type(Game_Editor* editor, Game_Editor_Entity_Type new_type);

/*! @brief Updates the game editor's selected entity type and variation.
 *
 * @note All entity edit operations will use the given type and variation.
 *
 *  @param[in] editor The game editor module.
 *  @param[in] type The new type of the game editor's selected entity.
 *  @param[in] variation The new variation of the game editor's selected entity.
 */
void update_editor_selected_entity(Game_Editor* editor, int type, int variation);

/*! @brief Updates the game editor.
 *
 * @note Processes user input to edit entities in the game board.
 *
 *  @param[in] editor The game editor module.
 *  @param[in] game_renderer The game renderer module.
 *  @param[in] game_camera The game camera module.
 *  @param[in] game_board The game board module.
 *  @param[in] game_clock The game clock module.
 *  @param[in] mouse_state The current mouse state.
 */
void update_game_editor(
    Game_Editor* editor,
    Game_Renderer* game_renderer,
    Game_Camera* game_camera,
    Game_Board* game_board,
    Game_Clock* game_clock,
    Mouse_State* mouse_state
);

// Draw the editor's visual components (gridlines, hover rectangle...).
// void render_editor(Editor* editor);

/*! @brief Frees memory occupied by the game editor module.
 *
 *  @param[in] editor The game editor module to free.
 */
void free_game_editor(Game_Editor* editor);
