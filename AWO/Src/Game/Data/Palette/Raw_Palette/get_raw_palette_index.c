#include <cglm/cglm.h>

#include "Game/Data/Palette/_palette.h"

GLfloat get_unit_palette_index(Unit_Variation unit_variation, GLboolean done)
{
    return get_palette_NDC_index( get_unit_palette_index_i(unit_variation, done) );
}

GLfloat get_tile_palette_index(Weather weather, GLboolean fog)
{
    return get_palette_NDC_index( get_tile_palette_index_i(weather, fog));
}

GLfloat get_property_palette_index(Unit_Variation unit_variation)
{
    return get_palette_NDC_index( get_property_palette_index_i(unit_variation) );
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

GLint get_raw_fog_property_palette_index_i()
{
    return (UNIT_PALETTE_COUNT + TILE_PALETTE_COUNT + PROP_PALETTE_COUNT) - 1;
}
