#include "Game/_game.h"

#include "Game/Data/Palette/palette.h"

static int flag = 0;

void add_to_sprite_batch__test_palette(Sprite_Batch* sprite_batch);

void render_game(Game* game)
{

    if (!flag) {
        flag = 1;
        Animation* test_tile;
        gather_tile_data(game->tiles_data, Forest, Default, NULL, NULL, &test_tile);

        GLfloat one = test_tile->frames[0].raw_top_left[0];
        GLfloat two = test_tile->frames[0].raw_top_left[1];

        printf("%.6f %.6f\n", one, two);

        // printf("%.16f %.16f\n", test_tile->frames[0].top_left[0], test_tile->frames[0].top_left[1]);

        fill_tiles_palette_pixels(game->tiles_renderer, one, two, get_tile_palette_index(Clear, 0));

        Animation* add_tile_1;
        gather_tile_data(game->tiles_data, River, Horizontal, NULL, NULL, &add_tile_1);

        update_tiles_pixel(
            game->tiles_renderer, 
            10, 
            10, 
            add_tile_1->frames[0].raw_top_left[0], 
            add_tile_1->frames[0].raw_top_left[1], 
            get_tile_palette_index(Clear, 0)
        );
    }

    render(game->tiles_renderer);

    // Draw main sprites
    // begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // add_to_sprite_batch__test_palette(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // draw_game_board(game->board, game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
