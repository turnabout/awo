#include "Game/_game.h"

#include "Game/Data/Palette/palette.h"

static int flag = 0;

static GLfloat offset_x = 0.0f;
static GLfloat offset_y = 0.0f;

void add_to_sprite_batch__test_palette(Sprite_Batch* sprite_batch);

void test_fill(Game* game)
{
    for (int x = 0; x < 21; x++) {
        for (int y = 0; y < 21; y++) {
            update_tiles_pixel(
                game->tiles_renderer, 
                x, 
                y, 
                (GLfloat)(x * 16), 
                (GLfloat)(y * 16), 
                get_tile_palette_index(Clear, 0)
            );
        }
    }
}

void render_game(Game* game)
{

    if (!flag) {
        flag = 1;
        Animation* test_tile;
        gather_tile_data(game->tiles_data, Bridge, Horizontal, NULL, NULL, &test_tile);

        GLfloat one = test_tile->frames[0].raw_top_left[0];
        GLfloat two = test_tile->frames[0].raw_top_left[1];

        fill_tiles_palette_pixels(game->tiles_renderer, one, two, get_tile_palette_index(Clear, 0));
        // test_fill(game);

        /*
        Animation* add_tile_1;
        gather_tile_data(game->tiles_data, Silo, Default, NULL, NULL, &add_tile_1);

        update_tiles_pixel(
            game->tiles_renderer, 
            10, 
            10, 
            add_tile_1->frames[0].raw_top_left[0], 
            add_tile_1->frames[0].raw_top_left[1], 
            get_tile_palette_index(Clear, 0)
        );
        */
    }

    if (get_key_state(KEY_A) == BUTTON_DOWN_START) {
        offset_x -= 16.0f;
        fill_tiles_palette_pixels(game->tiles_renderer, offset_x, offset_y, get_tile_palette_index(Clear, 0));
    }

    if (get_key_state(KEY_D) == BUTTON_DOWN_START) {
        offset_x += 16.0f;
        fill_tiles_palette_pixels(game->tiles_renderer, offset_x, offset_y, get_tile_palette_index(Clear, 0));
    }

    if (get_key_state(KEY_W) == BUTTON_DOWN_START) {
        offset_y -= 16.0f;
        fill_tiles_palette_pixels(game->tiles_renderer, offset_x, offset_y, get_tile_palette_index(Clear, 0));
    }

    if (get_key_state(KEY_S) == BUTTON_DOWN_START) {
        offset_y += 16.0f;
        fill_tiles_palette_pixels(game->tiles_renderer, offset_x, offset_y, get_tile_palette_index(Clear, 0));
    }

    render(game->tiles_renderer);

    // Draw main sprites
    // begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // add_to_sprite_batch__test_palette(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // draw_game_board(game->board, game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
