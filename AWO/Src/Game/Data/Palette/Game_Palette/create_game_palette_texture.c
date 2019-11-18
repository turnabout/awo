#include <stdlib.h>

#include "Game/Data/Palette/_palette.h"

GLuint create_game_palette_texture(
    GLuint raw_palette_texture, 
    Weather active_weather, 
    Unit_Variation player_armies[MAX_PLAYER_COUNT]
)
{
    Palette_Texture_Row* palette_texture_data = (Palette_Texture_Row*)malloc(
        sizeof(Palette_Texture_Row) * PALETTE_TEX_HEIGHT
    );

    glBindTexture(GL_TEXTURE_2D, raw_palette_texture);

    // Create the texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        PALETTE_TEX_WIDTH, 
        PALETTE_TEX_HEIGHT, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        palette_texture_data
    );

    free(palette_texture_data);

    return texture;
}
