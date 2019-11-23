#include <cglm/cglm.h>

#include "Game/Data/Palette/_palette.h"

// Currently active tile palette
#define ACTIVE_TILE_PALETTE_INDEX     0
#define ACTIVE_FOG_TILE_PALETTE_INDEX ACTIVE_TILE_PALETTE_INDEX + 1
#define ACTIVE_TILE_PALETTE_COUNT     2

// Player units palettes
#define PLAYER_UNITS_PALETTE_START    ACTIVE_TILE_PALETTE_COUNT
#define PLAYER_UNITS_PALETTE_COUNT    (REAL_PLAYER_INDEX_COUNT) * (2)

// Player property palettes
#define PLAYER_PROPERTIES_PALETTE_START ACTIVE_TILE_PALETTE_COUNT + PLAYER_UNITS_PALETTE_COUNT
#define PLAYER_PROPERTIES_PALETTE_COUNT PLAYER_INDEX_COUNT
#define FOG_PALETTE_INDEX               PLAYER_PROPERTIES_PALETTE_START + PLAYER_PROPERTIES_PALETTE_COUNT

GLfloat get_active_tile_palette_index(GLboolean fog)
{
    return get_palette_NDC_index(get_active_tile_palette_index_i(fog));
}

GLfloat get_player_unit_palette_index(Player_Index player_index, GLboolean done)
{
    return get_palette_NDC_index(get_player_unit_palette_index_i(player_index, done));
}

GLfloat get_player_property_palette_index(Player_Index player_index)
{
    return get_palette_NDC_index(get_player_property_palette_index_i(player_index));
}

GLfloat get_fog_property_palette_index()
{
    return get_palette_NDC_index(get_fog_property_palette_index_i());
}

GLuint get_active_tile_palette_index_i(GLboolean fog)
{
    return fog ? ACTIVE_FOG_TILE_PALETTE_INDEX : ACTIVE_TILE_PALETTE_INDEX;
}

GLuint get_player_unit_palette_index_i(Player_Index player_index, GLboolean done)
{
    return PLAYER_UNITS_PALETTE_START + ((player_index * 2) + done);
}

GLuint get_player_property_palette_index_i(Player_Index player_index)
{
    return PLAYER_PROPERTIES_PALETTE_START + player_index;
}

GLuint get_fog_property_palette_index_i()
{
    return FOG_PALETTE_INDEX;
}
