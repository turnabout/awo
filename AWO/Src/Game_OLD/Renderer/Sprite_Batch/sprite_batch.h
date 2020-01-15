#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/types.h>

#include "Game/Data/Animation/animation.h"

typedef struct Sprite_Batch Sprite_Batch;

typedef enum Sprite_Batch_Type {
    SPRITES_SPRITE_BATCH,
    FONTS_SPRITE_BATCH,
} Sprite_Batch_Type;

#define SPRITE_BATCH_TYPE_LAST  FONTS_SPRITE_BATCH
#define SPRITE_BATCH_TYPE_COUNT SPRITE_BATCH_TYPE_LAST + 1

/*! @brief Initializes a sprite batch object.
 *
 *  @param[in] shader_program The shader_program program associated with this sprite batch.
 *  @param[in] texture The texture associated with this sprite batch.
 *  @param[in] palettes_texture The palette texture associated with this sprite batch. Used to 
 *  specify which colors to apply to greyscale sprites. 0 for none.
 *  @param[in] max_elements Maximum amount of elements this sprite batch can queue.
 *  @return Pointer to the created sprite batch object.
 */
Sprite_Batch* create_sprite_batch(
    GLuint shader_program,
    GLuint texture,
    GLuint palette_texture,
    int max_elements
);

/*! @brief Begins a new sprite batch queue.
 *
 *  @param[in] sprite_batch The sprite batch object to add to.
 */
void begin_sprite_batch(Sprite_Batch* sprite_batch);

/*! @brief Adds a frame's element to the sprite batch object queue.
 *
 *  @param[in] sprite_batch The sprite batch object used to queue the element.
 *  @param[in] dst The on-screen destination coordinates. (x/y)
 *  @param[in] frame_data The frame's data.
 *  @param[in] palette_index Index of which palette used to draw the added sprite.
 */
void add_to_sprite_batch(
    Sprite_Batch* sprite_batch,
    vec2 dst,
    Frame* frame_data,
    GLfloat palette_index
);

/*! @brief Ends the sprite batch queue, drawing the accumulated elements.
 *
 *  @param[in] sprite_batch The sprite batch object.
 */
void end_sprite_batch(Sprite_Batch* sprite_batch);

/*! @brief Frees the sprite batch's allocated data.
 *
 *  @param[in] sprite_batch The sprite batch object.
 */
void free_sprite_batch(Sprite_Batch* sprite_batch);
void add_to_sprite_batch__test_palette(Sprite_Batch* sprite_batch);