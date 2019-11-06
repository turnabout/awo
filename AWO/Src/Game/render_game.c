#include "Game/_game.h"

#include "Game/Data/Palette/palette.h"

static int flag = 0;

void add_to_sprite_batch__test_palette(Sprite_Batch* sprite_batch);

void render_game(Game* game)
{

    if (!flag) {
        flag = 1;
        Animation* test_tile;
        gather_tile_data(game->tiles_data, Bridge, Horizontal, NULL, NULL, &test_tile);

        GLfloat one = test_tile->frames[0].top_left[0];
        GLfloat two = test_tile->frames[0].top_left[1];

        update_tiles_palette_pixel(game->tiles_renderer, 0, 0, one, two, get_tile_palette_index(Clear, 0));
        update_tiles_palette_pixel(game->tiles_renderer, 1, 0, one, two, get_tile_palette_index(Clear, 0));
    }


    // printf("%.2f %.2f\n", test_tile->frames[0].top_left[0], test_tile->frames[0].top_left[1]);


    render(game->tiles_renderer, 0, 0);

    // Draw main sprites
    // begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // add_to_sprite_batch__test_palette(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // draw_game_board(game->board, game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
