#include <cglm/cglm.h>

#include "Game/Data/Palette/_palette.h"

// Array of every palette indexes NDC y values.
static GLfloat* palette_NDC_indexes;

void init_palette_NDC_indexes(int palette_count)
{
    palette_NDC_indexes = malloc(sizeof(GLfloat) * palette_count);

    // Make the projection matrix used to transform palette texture Y coordinates into NDC
    mat4 projection;
    glm_ortho(0.0f, (float)PALETTE_TEX_WIDTH, 0.0f, (float)palette_count, -1.0f, 1.0f, projection);

    for (int i = 0; i < palette_count; i++) {
        vec4 position = {0.0f, (float)i, 0.0f, 1.0f};
        glm_mat4_mulv(projection, position, position);
        palette_NDC_indexes[i] = (position[1] / 2.0f) + 0.50f;

        printf("%.12f\n", palette_NDC_indexes[i]);
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
    return palette_NDC_indexes[UNIT_VAR_LAST + weather];
}

void free_palette_NDC_indexes()
{
    free(palette_NDC_indexes);
}
