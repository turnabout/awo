#include <cglm/cglm.h>

#include "Game/Data/Palette/_palette.h"

// Array of every palette indexes NDC y values.
static GLfloat* palette_NDC_indexes;

void init_palette_NDC_indexes(int palette_count)
{
    palette_NDC_indexes = malloc(sizeof(GLfloat) * palette_count);

    for (int i = 0; i < palette_count; i++) {
        palette_NDC_indexes[i] = (float)i / (float)palette_count;
    }
}

// Unit variation palette indexes are stored first
GLfloat get_unit_palette_index(Unit_Variation unit_var)
{
    return palette_NDC_indexes[unit_var];
}

// Tile weather palette indexes are stored second, followed by fog versions
GLfloat get_tile_palette_index(Weather weather)
{
    return palette_NDC_indexes[UNIT_VAR_COUNT + weather];
}

void free_palette_NDC_indexes()
{
    free(palette_NDC_indexes);
}
