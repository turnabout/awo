#pragma once

#include <cglm/types.h>

typedef struct Renderer Renderer;

Renderer* create_renderer(
    GLuint sprite_sheet_tex,
    GLuint palette_tex,
    GLuint shader,
    GLuint width,
    GLuint height
);

void render(Renderer* renderer, int x_offset, int y_offset);

void update_tiles_pixel(
    Renderer* renderer,
    GLuint x,
    GLuint y,
    GLfloat R,
    GLfloat G,
    GLfloat B
);

void fill_tiles_palette_pixels(Renderer* renderer, GLfloat R, GLfloat G, GLfloat B);