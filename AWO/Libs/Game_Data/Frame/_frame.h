#pragma once

#include "Game_Data/Frame/frame.h"

/*! @brief Populates the contents of a previously-allocated frame.
 *
 *  @param[out] frame_ptr Pointer to the previously-allocated frame.
 *  @param[in] frame_JSON JSON object describing the frame.
 *  @param[in] ss_width The sprite sheet's width.
 *  @param[in] ss_height The sprite sheet's height.
 */
void populate_frame(Frame* frame, cJSON* frame_JSON, float ss_width, float ss_height);
