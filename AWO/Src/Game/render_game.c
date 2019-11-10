#include <cglm/cglm.h>

#include "Game/_game.h"
#include "Game/Data/Palette/palette.h"

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

    static GLfloat offset_x = 0.0f;
    static GLfloat offset_y = 0.0f;

    /*
    if (!flag) {
        flag = 1;
        Animation* test_tile;
        gather_tile_data(game->tiles_data, Plain, Default, NULL, NULL, &test_tile);

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
        fill_tiles_layer_mem(game->tiles_layer,(vec4) {offset_x,offset_y,get_tile_palette_index(Clear, 0),0.0f});
        printf("%d,%d\n", (int)offset_x, (int)offset_y);
    }

    if (get_key_state(KEY_D) == BUTTON_DOWN_START) {
        offset_x += 16.0f;
        fill_tiles_layer_mem(game->tiles_layer,(vec4) {offset_x,offset_y,get_tile_palette_index(Clear, 0),0.0f});
        printf("%d,%d\n", (int)offset_x, (int)offset_y);
    }

    if (get_key_state(KEY_W) == BUTTON_DOWN_START) {
        offset_y -= 16.0f;
        fill_tiles_layer_mem(game->tiles_layer,(vec4) {offset_x,offset_y,get_tile_palette_index(Clear, 0),0.0f});
        printf("%d,%d\n", (int)offset_x, (int)offset_y);
    }

    if (get_key_state(KEY_S) == BUTTON_DOWN_START) {
        offset_y += 16.0f;
        fill_tiles_layer_mem(game->tiles_layer,(vec4) {offset_x,offset_y,get_tile_palette_index(Clear, 0),0.0f});
        printf("%d,%d\n", (int)offset_x, (int)offset_y);
    }

    if (get_key_state(KEY_UP) == BUTTON_DOWN) {
        scale += 1.0f;
        update_view_matrix(game);
    }

    if (get_key_state(KEY_DOWN) == BUTTON_DOWN) {
        scale -= 1.0f;
        update_view_matrix(game);
    }

    render_tiles_layer(game->tiles_layer);
*/

    // Draw main sprites
    // begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // draw_game_board(game->board, game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
