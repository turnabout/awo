#include <stdlib.h>

#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/Render_Grid/_render_grid.h"

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
        GL_RGBA32F, 
        render_grid->width, 
        render_grid->height, 
        0, 
        GL_RGBA, 
        GL_FLOAT, 
        NULL
    );
}

Render_Grid* create_render_grid(GLuint width, GLuint height, GLuint y_offset, GLuint tiles_shader)
{
    Render_Grid* render_grid = malloc(sizeof(Render_Grid));

    render_grid->width = width;
    render_grid->height = height;
    render_grid->dirty = TRUE;

    init_render_grid_texture(render_grid);

    render_grid->VAO = get_render_grid_VAO(width, height, y_offset, tiles_shader);

    render_grid->pixel_data = malloc(sizeof(vec4) * render_grid->width * render_grid->height);

    return render_grid;
}

void render_r_grid(Render_Grid* render_grid)
{
    // Bind this grid's texture
    glActiveTexture(GL_TEXTURE2); 
    glBindTexture(GL_TEXTURE_2D, render_grid->grid_texture);

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
    
void free_render_grid(Render_Grid* render_grid)
{
    if (render_grid != NULL) {

        if (render_grid->pixel_data != NULL) {
            free(render_grid->pixel_data);
        }

        free(render_grid);
    }
}