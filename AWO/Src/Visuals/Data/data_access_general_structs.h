#pragma once
#include <SDL.h>

/**
 * \brief Represents an animation and its frames.
 */
typedef struct
{
    int count;
    SDL_Rect* frames;
} Animation;

/**
 * \brief Represents the sprite sheet meta data for a data structure.
 */
typedef struct
{
    int src_x;
    int src_y;
    int src_width;
    int src_height;
    int dst_width;
    int dst_height;
} SS_Meta_Data;
