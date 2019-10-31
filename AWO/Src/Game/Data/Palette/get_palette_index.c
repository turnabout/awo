#include "Game/Data/Palette/palette.h"

// Unit variation palette indexes are stored first
GLuint get_unit_palette_index(Unit_Variation unit_var)
{
    return (GLuint)unit_var;
}

// Tile weather palette indexes are stored second, followed by fog versions
GLuint get_tile_palette_index(Weather weather, GLboolean fog)
{
    return (GLuint)UNIT_VAR_LAST + (fog)
        ? (GLuint)(WEATHER_COUNT + weather)
        : (GLuint)weather;
}
