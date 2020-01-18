#pragma once

/*! @brief Generic game update callback function.
 */
typedef void (*Game_Update_CB)(void* game, float delta_time);

/*! @brief Generic game render callback function.
 */
typedef void (*Game_Render_CB)(void* game);
