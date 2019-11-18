#include <cglm/cglm.h>

#include "Game/Data/Palette/_palette.h"

GLfloat get_active_tile_palette_index(GLboolean fog)
{
    return get_palette_NDC_index(
        fog ? ACTIVE_FOG_TILE_PALETTE_INDEX : ACTIVE_TILE_PALETTE_INDEX
    );
}
