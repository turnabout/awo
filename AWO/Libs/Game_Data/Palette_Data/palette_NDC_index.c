#include <cglm/cglm.h>

#include "Game_Data/Palette_Data/_palette_data.h"
#include "AWO/game_message.h"

// Array of every palette indexes NDC y values.
static GLfloat palette_NDC_indexes[PALETTE_TEX_HEIGHT];

static Bool initialized = FALSE;

void init_palette_NDC_indexes()
{
    for (int i = 0; i < PALETTE_TEX_HEIGHT; i++) {
        palette_NDC_indexes[i] = (float)i / (float)PALETTE_TEX_HEIGHT;
    }

    initialized = TRUE;
}

GLfloat get_palette_NDC_index(GLuint palette_row)
{
    if (!initialized) {
        printe("Attempting to get a palette NDC index before they were initialized");
        return 0;
    }

    return palette_NDC_indexes[palette_row];
}
