#pragma once

/*! @brief Generic game update callback function.
 */
typedef void (*Game_Update_CB)(void* game, float delta_time);

/*! @brief Generic game render callback function.
 */
typedef void (*Game_Render_CB)(void* game);

/*! @brief Function called to update the game's dimensions internally.
 *  Called after the game window's dimensions were changed.
 */
typedef void (*Game_Dimensions_Update_CB)(Game* game, int width, int height);
