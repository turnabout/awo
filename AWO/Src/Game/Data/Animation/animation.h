#pragma once

#include <cglm/types.h>
#include <cJSON.h>

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

    // Width/tiles_height of this frame.
    vec2 dimensions;  
} Frame;

/*! @brief Animation object.
 *
 * Contains a reference to the first of many frames making up an animation.
 */
typedef struct Animation {
    int count;
    Frame* frames;
} Animation;

/*! @brief Creates an animation struct from the given cJSON animation array object.
 *
 *  @param[in] animation_json The JSON representing this animation and its frames.
 *  @param[in] ss_width The tiles_width of the sprite sheet this animation comes from.
 *  @param[in] ss_height The tiles_height of the sprite sheet this animation comes from.
 */
Animation* create_animation(const cJSON* animation_JSON, int ss_width, int ss_height);

/*! @brief Frees an animation's allocated memory.
 *
 *  @param[in] animation The animation to free.
 */
void free_animation(Animation* animation);

/*! @brief Gets pointer to the first frame in an Animation.
 *
 *  @param[in] animation The animation object from which to fetch the frame.
 *  @param[out] count Filled in with the frame count in the animation.
 */
// Frame* get_animation_frames(Animation* animation, int* count);

#ifdef _DEBUG
// 
/*! @brief Prints an Animation's contents.
 *
 *  @param[in] animation The animation object to print.
 */
void print_animation(Animation* animation);
#endif
