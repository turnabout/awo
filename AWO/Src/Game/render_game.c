#include "Game/_game.h"

#include "Game/Data/Palette/palette.h"

void render_game(Game* game)
{
    static int flag = 0;

    static GLfloat offset_x = 0.0f;
    static GLfloat offset_y = 0.0f;

    if (!flag) {
        flag = 1;
        Animation* test_tile;
        gather_tile_data(game->tiles_data, Bridge, Horizontal, NULL, NULL, &test_tile);

        fill_tiles_layer_mem(
            game->tiles_layer,
            (vec4) {
                test_tile->frames[0].raw_top_left[0],
                test_tile->frames[0].raw_top_left[1],
                get_tile_palette_index(Clear, 0),
                0.0f
            }
        );
    }

    if (get_key_state(KEY_A) == BUTTON_DOWN_START) {
        offset_x -= 16.0f;
    }

    if (get_key_state(KEY_D) == BUTTON_DOWN_START) {
        offset_x += 16.0f;
    }

    if (get_key_state(KEY_W) == BUTTON_DOWN_START) {
        offset_y -= 16.0f;
    }

    if (get_key_state(KEY_S) == BUTTON_DOWN_START) {
        offset_y += 16.0f;
    }

    render_tiles_layer(game->tiles_layer);

    // Draw main sprites
    // begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // draw_game_board(game->board, game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
