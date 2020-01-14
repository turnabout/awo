#include <cglm/cglm.h>

#include "Game_Data/Palette_Data/_palette_data.h"

// Array of every palette indexes NDC y values.
static GLfloat palette_NDC_indexes[PALETTE_TEX_HEIGHT];

void init_palette_NDC_indexes()
{
    for (int i = 0; i < PALETTE_TEX_HEIGHT; i++) {
        palette_NDC_indexes[i] = (float)i / (float)PALETTE_TEX_HEIGHT;
    }
}

GLfloat get_palette_NDC_index(GLuint palette_row)
{
    return palette_NDC_indexes[palette_row];
}
