#pragma once

#include <cglm/types.h>
#include <cJSON.h>

/*! @brief Frame object.
 *
 * Describes the source data of a frame within the sprite sheet.
 */
typedef struct Frame {
    vec4 top_left;     // This frame's source coordinates, in Normalized Device Coordinates
    vec4 top_right;    // Indexes go x/y/z/w
    vec4 bottom_left;
    vec4 bottom_right;

    vec2 dimensions;  // Width/height of this frame. Indexes go w/h
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
 *  @param[in] projection The projection matrix used to convert frame source coordinates 
 *  to NDC.
 */
Animation* create_animation(const cJSON* animation_JSON, mat4 projection);

// 
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
