#pragma once

#include <cglm/types.h>
#include <cjson/cJSON.h>

#include "Utilities/utilities.h"

/*! @brief Frame object.
 *
 * Describes the source data of a frame within the sprite sheet.
 */
typedef struct Frame {
    // This frame's source coordinates, in Normalized Device Coordinates
    vec4 top_left;
    vec4 top_right;
    vec4 bottom_left;
    vec4 bottom_right;

    // This frame's raw top-left source coordinates, in pixels
    vec2 raw_top_left;

    // Height of this frame, in pixels.
    Uint8 width, height;
} Frame;

/*! @brief Creates a frame struct from the given frame JSON.
 *
 *  @param[in] frame_JSON JSON object describing the frame.
 *  @param[in] ss_width The sprite sheet's width.
 *  @param[in] ss_height The sprite sheet's height.
 *  @return The created Frame struct.
 */
Frame* create_frame(cJSON* frame_JSON, int ss_width, int ss_height);

/*! @brief Frees the memory occupied by a frame.
 *
 *  @param[in] frame The frame to free.
 */
void free_frame(Frame* frame);