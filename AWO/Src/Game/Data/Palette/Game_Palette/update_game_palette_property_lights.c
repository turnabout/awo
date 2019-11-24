#include "Game/Data/Palette/game_palette.h"

#define PROPERTY_AFFECTED_ROWS_AMOUNT PLAYER_INDEX_COUNT - 1 // - 1 to ignore neutral properties
#define PROPERTY_LIGHTS_PALETTE_INDEX 111

static Bool lights_on = FALSE;

static GLubyte lights_on_color[PROPERTY_AFFECTED_ROWS_AMOUNT][4] = {
    { 248, 248, 112, 255 },
    { 248, 248, 112, 255 },
    { 248, 248, 112, 255 },
    { 248, 248, 112, 255 },
};

static GLubyte lights_off_color[PROPERTY_AFFECTED_ROWS_AMOUNT][4] = {
    { 120, 104, 120, 255 },
    { 120, 104, 120, 255 },
    { 120, 104, 120, 255 },
    { 120, 104, 120, 255 },
};

void update_game_palette_property_lights(GLuint game_palette)
{
    glBindTexture(GL_TEXTURE_2D, game_palette);

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,

        // X/Y offset
        PROPERTY_LIGHTS_PALETTE_INDEX,
        get_player_property_palette_index_i(Player_Index_0),

        // Width/Height
        1,
        PROPERTY_AFFECTED_ROWS_AMOUNT,

        GL_RGBA,
        GL_UNSIGNED_BYTE,
        (lights_on) ? lights_off_color : lights_on_color
    );

    lights_on ^= TRUE;
}