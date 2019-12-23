#pragma once

#include "Include/game_editor.h"
#include "Game/Board/game_board.h"
#include "Game/Camera/game_camera.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Unit/units_data.h"
#include "Game/Inputs/Mouse/mouse.h"

/*! @brief The game editor module. Edits entities in the game board in design room mode according
 *  to user input.
 */
typedef struct Game_Editor Game_Editor;

/*! @brief Creates the game editor module.
 *
 * @note Used in "design room" game mode to fully edit the stage currently loaded by the game 
 * board.
 *
 *  @param[in] tiles_data
 *  @param[in] units_data
 *  @param[in] window_width Pointer to the game window's width.
 *  @param[in] window_height Pointer to the game window's height.
 *  @return The created game editor module.
 */
Game_Editor* create_game_editor(
    Tiles_Data* tiles_data,
    Units_Data* units_data,
    int* window_width,
    int* window_height
);

/*! @brief Updates the game editor's selected entity.
 *
 * @note All following entity edit operations will use the entity set here.
 *
 *  @param[in] editor The game editor module.
 *  @param[in] kind The kind of entity the game editor should update. Either tiles or units.
 *  @param[in] type The new type of the game editor's selected entity.
 *  @param[in] variation The new variation of the game editor's selected entity.
 */
void update_editor_selected_entity(
    Game_Editor* editor,
    Game_Editor_Entity_Kind kind,
    int type,
    int variation
);

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
