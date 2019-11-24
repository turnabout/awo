#include <cglm/cglm.h>

#include "Game/_game.h"
#include "Game/Data/Palette/game_palette.h"

static GLfloat scale = 16.0f;

void update_view_matrix(Game* game)
{
    mat4 view = GLM_MAT4_IDENTITY_INIT;
    glm_scale(view, (vec3) { (GLfloat)scale, (GLfloat)scale, 1.0f });

    // update_tiles_layer_view_matrix(game->tiles_layer, view);
}

void render_game(Game* game)
{
    static int flag = 0;

    if (!flag) {
        flag = 1;
    }

    render_tiles_layers();

    if (get_key_state(KEY_A) == BUTTON_DOWN_START) {
        update_active_tile_palette(Clear, game->palette_texture, game->raw_palette_texture);
    }

    if (get_key_state(KEY_S) == BUTTON_DOWN_START) {
        update_active_tile_palette(Rain, game->palette_texture, game->raw_palette_texture);
    }

    if (get_key_state(KEY_D) == BUTTON_DOWN_START) {
        update_active_tile_palette(Snow, game->palette_texture, game->raw_palette_texture);
    }

    if (get_key_state(KEY_1) == BUTTON_DOWN_START) {
        update_game_palette_property_lights(game->palette_texture);
    }

    // Draw main sprites
    // begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // draw_game_board(game->board, game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
