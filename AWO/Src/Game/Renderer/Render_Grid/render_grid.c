#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "conf.h"
#include "types.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/Render_Grid/render_grid.h"

// Number used to divide values that are to be stored in the grid's memory, before sending to GPU.
// This is necessary so the fragment shader can properly receive the value.
#define VALUE_PACK_DIVISOR 510.0f

struct Render_Grid {

    // The render grid's pixel data.
    vec4* pixel_data;

    // The texture used by this grid to render.
    GLuint grid_texture;

    // VAO used to render this render grid.
    GLuint VAO;

    // Dimensions of the render grid.
    Uint8 width, height;

    // Whether the tiles layer's pixel data was changed since the last render.
    Bool dirty;
};

void init_render_grid_texture(Render_Grid* render_grid)
{
    glGenTextures(1, &render_grid->grid_texture);
    glBindTexture(GL_TEXTURE_2D, render_grid->grid_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        render_grid->width, 
        render_grid->height, 
        0, 
        GL_RGBA, 
        GL_FLOAT, 
        NULL
    );
}

Render_Grid* create_render_grid(GLuint width, GLuint height, GLuint vertical_offset)
{
    Render_Grid* render_grid = (Render_Grid*)malloc(sizeof(Render_Grid));

    render_grid->width = width;
    render_grid->height = height;
    render_grid->dirty = TRUE;

    init_render_grid_texture(render_grid);

    render_grid->VAO = get_render_grid_VAO(width, height, vertical_offset);

    render_grid->pixel_data = malloc(sizeof(vec4) * render_grid->width * render_grid->height);

    return render_grid;
}

void render_r_grid(Render_Grid* render_grid)
{
    // Bind this grid's texture
    glActiveTexture(GL_TEXTURE2); 
    glBindTexture(GL_TEXTURE_2D, render_grid->grid_texture);

    // Set tiles layers
    glBindVertexArray(render_grid->VAO);

    // Update the grid texture's GPU pixel data only if it was changed since the last render
    if (render_grid->dirty) {
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            render_grid->width,
            render_grid->height,
            GL_RGBA,
            GL_FLOAT,
            render_grid->pixel_data
        );

        render_grid->dirty = TRUE;
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
    
void update_render_grid_pixels(
    Render_Grid* tiles_layer, 
    Point* points, 
    Uint16 points_count, 
    vec4 value
)
{
    GLfloat copied_value[4] = {
        value[0] / VALUE_PACK_DIVISOR, 
        value[1] / VALUE_PACK_DIVISOR, 
        value[2], 
        value[3] 
    };

    for (int i = 0; i < points_count; i++) {
        memcpy(
            (tiles_layer->pixel_data + points[i].x + (points[i].y * tiles_layer->width)), 
            &copied_value, 
            sizeof(copied_value)
        );
    }

    tiles_layer->dirty = TRUE;
}

void update_render_grid_pixels_low(
    Render_Grid* tiles_layer, 
    Point* points, 
    Uint16 points_count, 
    vec2 value
)
{
    GLfloat copied_value[2] = {
        value[0] / VALUE_PACK_DIVISOR, 
        value[1] / VALUE_PACK_DIVISOR, 
    };

    for (int i = 0; i < points_count; i++) {
        memcpy(
            (tiles_layer->pixel_data + points[i].x + (points[i].y * tiles_layer->width)), 
            &copied_value, 
            sizeof(copied_value)
        );
    }

    tiles_layer->dirty = TRUE;
}

void fill_render_grid_pixels(Render_Grid* tiles_layer, vec4 values)
{
    GLfloat stored_values[4] = {
        values[0] / VALUE_PACK_DIVISOR, 
        values[1] / VALUE_PACK_DIVISOR, 
        values[2], 
        values[3] 
    };

    for (int y = 0; y < (int)tiles_layer->height; y++) {
        for (int x = 0; x < (int)tiles_layer->width; x++) {
            memcpy(
                (tiles_layer->pixel_data + x + (y * tiles_layer->width)), 
                &stored_values, 
                sizeof(stored_values)
            );
        }
    }

    tiles_layer->dirty = TRUE;
}

void free_render_grid(Render_Grid* tiles_layer)
{
    if (tiles_layer != NULL) {
        free(tiles_layer->pixel_data);
        free(tiles_layer);
    }
}