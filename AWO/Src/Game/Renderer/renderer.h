#pragma once

typedef struct Renderer Renderer;

Renderer* create_renderer(GLuint sprite_sheet_tex, GLuint palette_tex, GLuint shader);

void render(Renderer* renderer, int x_offset, int y_offset);

void update_tiles_palette_pixel(
    Renderer* renderer,
    GLuint x,
    GLuint y,
    GLfloat R,
    GLfloat G,
    GLfloat B
);