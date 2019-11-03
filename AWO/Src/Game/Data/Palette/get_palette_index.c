#include <cglm/cglm.h>

#include "Game/Data/Palette/_palette.h"

// Array of every palette indexes NDC y values.
static GLfloat palette_NDC_indexes[PALETTE_TEX_HEIGHT];

void init_palette_NDC_indexes()
{
    for (int i = 0; i < PALETTE_TEX_HEIGHT; i++) {
        palette_NDC_indexes[i] = (float)i / (float)PALETTE_TEX_HEIGHT;
    }
}

GLfloat get_unit_palette_index(Unit_Variation unit_variation, GLboolean done)
{
    return palette_NDC_indexes[ get_unit_palette_index_i(unit_variation, done) ];
}

GLfloat get_tile_palette_index(Weather weather, GLboolean fog)
{
    return palette_NDC_indexes[ get_tile_palette_index_i(weather, fog) ];
}

GLfloat get_property_palette_index(Unit_Variation unit_variation)
{
    return palette_NDC_indexes[ get_property_palette_index_i(unit_variation) ];
}

GLint get_unit_palette_index_i(Unit_Variation unit_variation, GLboolean done)
{
    return (unit_variation * 2) + done;
}

GLint get_tile_palette_index_i(Weather weather, GLboolean fog)
{
    return UNIT_PALETTE_COUNT + (weather * 2) + fog;
}

GLint get_property_palette_index_i(Unit_Variation unit_variation)
{
    return UNIT_PALETTE_COUNT + TILE_PALETTE_COUNT + unit_variation;
}
