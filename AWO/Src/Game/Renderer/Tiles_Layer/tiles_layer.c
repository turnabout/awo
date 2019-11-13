#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/Tiles_Layer/tiles_layer.h"

struct Tiles_Layer {

    // The tiles layer texture.
    GLuint tiles_texture;

    // This tiles layer's tiles texture pixel data.
    vec4* pixel_data;

    // Dimensions of the tiles layer, in tiles.
    int tiles_width, tiles_height;
};

void init_tiles_texture(Tiles_Layer* tiles_layer)
{
    glGenTextures(1, &tiles_layer->tiles_texture);
    glBindTexture(GL_TEXTURE_2D, tiles_layer->tiles_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        tiles_layer->tiles_width, 
        tiles_layer->tiles_height, 
        0, 
        GL_RGBA, 
        GL_FLOAT, 
        NULL
    );
}

Tiles_Layer* create_tiles_layer(GLuint tiles_layer_width, GLuint tiles_layer_height)
{
    Tiles_Layer* tiles_layer = (Tiles_Layer*)malloc(sizeof(Tiles_Layer));

    tiles_layer->tiles_width = tiles_layer_width;
    tiles_layer->tiles_height = tiles_layer_height;

    init_tiles_texture(tiles_layer);
    tiles_layer->pixel_data = malloc(sizeof(vec4) * tiles_layer->tiles_width * tiles_layer->tiles_height);

    return tiles_layer;
}

void render_tiles_layer(Tiles_Layer* tiles_layer)
{
    // Set this layer's tiles texture as active
    glActiveTexture(GL_TEXTURE2); 
    glBindTexture(GL_TEXTURE_2D, tiles_layer->tiles_texture);

    // Update tiles texture with current contents of tiles_layer's pixel data
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        0,
        tiles_layer->tiles_width,
        tiles_layer->tiles_height,
        GL_RGBA,
        GL_FLOAT,
        tiles_layer->pixel_data
    );

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void update_tiles_layer_pixel(Tiles_Layer* tiles_layer, GLuint x, GLuint y, vec4 values)
{
    GLfloat stored_values[4] = {
        values[0] / 510.0f, 
        values[1] / 510.0f, 
        values[2], 
        values[3] 
    };

    memcpy(
        (tiles_layer->pixel_data + x + (y * tiles_layer->tiles_width)), 
        &stored_values, 
        sizeof(stored_values)
    );
}

void update_tiles_layer_pixel_low(Tiles_Layer* tiles_layer, GLuint x, GLuint y, vec2 values)
{
    GLfloat stored_values[2] = {
        values[0] / 510.0f, 
        values[1] / 510.0f, 
    };

    memcpy(
        (tiles_layer->pixel_data + x + (y * tiles_layer->tiles_width)), 
        &stored_values, 
        sizeof(stored_values)
    );
}

void fill_tiles_layer_pixels(Tiles_Layer* tiles_layer, vec4 values)
{
    glBindTexture(GL_TEXTURE_2D, tiles_layer->tiles_texture);

    GLfloat stored_values[4] = {
        values[0] / 510.0f, 
        values[1] / 510.0f, 
        values[2], 
        values[3] 
    };

    for (int y = 0; y < (int)tiles_layer->tiles_height; y++) {
        for (int x = 0; x < (int)tiles_layer->tiles_width; x++) {
            memcpy(
                (tiles_layer->pixel_data + x + (y * tiles_layer->tiles_width)), 
                &stored_values, 
                sizeof(stored_values)
            );
        }
    }
}

void bind_tile_texture(Tiles_Layer* tiles_layer)
{
    glBindTexture(GL_TEXTURE_2D, tiles_layer->tiles_texture);
}

void free_tiles_layer(Tiles_Layer* tiles_layer)
{
    if (tiles_layer != NULL) {
        free(tiles_layer->pixel_data);
        free(tiles_layer);
    }
}