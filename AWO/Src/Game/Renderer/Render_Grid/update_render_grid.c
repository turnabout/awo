#include <string.h>

#include "Game/Renderer/Render_Grid/_render_grid.h"

// Number used to divide values that are to be stored in the grid's memory, before sending to GPU.
// This is necessary so the fragment shader can properly receive the value.
#define PIXEL_VALUE_PACK_DIVISOR 510.0f

void update_render_grid_pixel(
    Render_Grid* render_grid, 
    Uint8 x,
    Uint8 y,
    vec4 value
)
{
    GLfloat pixel[4] = {
        value[0] / PIXEL_VALUE_PACK_DIVISOR, 
        value[1] / PIXEL_VALUE_PACK_DIVISOR, 
        value[2], 
        value[3] 
    };

    memcpy(
        (render_grid->pixel_data + x + (y * render_grid->width)), 
        &pixel, 
        sizeof(pixel)
    );

    render_grid->dirty = TRUE;
}

void update_render_grid_pixel_high(
    Render_Grid* render_grid,
    Uint8 x,
    Uint8 y,
    vec2 value
)
{
    GLfloat pixel_high[2] = {
        value[0],
        value[1],
    };

    // TODO
    // render_grid->pixel_data[0] = value[0];

    // (&(render_grid->pixel_data + x + (y * render_grid->width)))[2] = value[0];

    memcpy(
        ((render_grid->pixel_data + x + (y * render_grid->width))), 
        &pixel_high, 
        sizeof(pixel_high)
    );

    render_grid->dirty = TRUE;

}

void update_render_grid_pixel_low(
    Render_Grid* render_grid, 
    Uint8 x,
    Uint8 y,
    vec2 value
)
{
    GLfloat pixel_low[2] = {
        value[0] / PIXEL_VALUE_PACK_DIVISOR, 
        value[1] / PIXEL_VALUE_PACK_DIVISOR, 
    };

    memcpy(
        (render_grid->pixel_data + x + (y * render_grid->width)), 
        &pixel_low, 
        sizeof(pixel_low)
    );

    render_grid->dirty = TRUE;
}

void fill_render_grid_pixels(Render_Grid* render_grid, vec4 values)
{
    GLfloat pixel[4] = {
        values[0] / PIXEL_VALUE_PACK_DIVISOR, 
        values[1] / PIXEL_VALUE_PACK_DIVISOR, 
        values[2], 
        values[3] 
    };

    for (int y = 0; y < (int)render_grid->height; y++) {
        for (int x = 0; x < (int)render_grid->width; x++) {
            memcpy(
                (render_grid->pixel_data + x + (y * render_grid->width)), 
                &pixel, 
                sizeof(pixel)
            );
        }
    }

    render_grid->dirty = TRUE;
}
