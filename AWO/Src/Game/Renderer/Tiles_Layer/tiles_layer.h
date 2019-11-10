#pragma once

#include <cglm/types.h>

typedef struct Tiles_Layer Tiles_Layer;

Tiles_Layer* create_tiles_layer(
    GLuint sprite_sheet_tex,
    GLuint palette_tex,
    GLuint shader,
    GLuint width,
    GLuint height
);

void render_tiles_layer(Tiles_Layer* tiles_layer);

void update_tiles_layer_mem(Tiles_Layer* tiles_layer, GLuint x, GLuint y, vec4 values);

void fill_tiles_layer_mem(Tiles_Layer* renderer, vec4 values);

void update_tiles_layer_view_matrix(Tiles_Layer* tiles_layer, mat4 view);

void free_tiles_layer(Tiles_Layer* tiles_layer);
