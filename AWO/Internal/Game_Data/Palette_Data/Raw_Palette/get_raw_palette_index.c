#include <cglm/cglm.h>

#include "Game_Data/Palette_Data/_palette_data.h"

GLfloat get_raw_unit_palette_index(Army_Type unit_variation, Bool done)
{
    return get_palette_NDC_index( get_raw_unit_palette_index_i(unit_variation, done) );
}

GLfloat get_raw_tile_palette_index(Weather weather, Bool fog)
{
    return get_palette_NDC_index( get_raw_tile_palette_index_i(weather, fog));
}

GLfloat get_raw_property_palette_index(Army_Type unit_variation)
{
    return get_palette_NDC_index( get_raw_property_palette_index_i(unit_variation) );
}

GLuint get_raw_unit_palette_index_i(Army_Type unit_variation, Bool done)
{
    return (unit_variation * 2) + done;
}

GLuint get_raw_tile_palette_index_i(Weather weather, Bool fog)
{
    return UNIT_PALETTE_COUNT + (weather * 2) + fog;
}

GLuint get_raw_property_palette_index_i(Army_Type unit_variation)
{
    return UNIT_PALETTE_COUNT + TILE_PALETTE_COUNT + unit_variation;
}

GLuint get_raw_fog_property_palette_index_i()
{
    return (UNIT_PALETTE_COUNT + TILE_PALETTE_COUNT + PROP_PALETTE_COUNT) - 1;
}
