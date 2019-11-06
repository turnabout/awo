#include "Game/_game.h"

#include "Game/Data/Palette/palette.h"

void add_to_sprite_batch__test_palette(Sprite_Batch* sprite_batch);

void render_game(Game* game)
{

    Animation* tile_animation;
    gather_tile_data(game->tiles_data, Plain, Default, NULL, NULL, &tile_animation);

    tile_animation->frames[0].top_left[0];

    update_tiles_palette_pixel(
        game->tiles_renderer, 
        0,
        0, 
        tile_animation->frames[0].top_left[0],
        tile_animation->frames[0].top_left[1]
    );

    render(game->tiles_renderer, 0, 0);

    // Draw main sprites
    // begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // add_to_sprite_batch__test_palette(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // draw_game_board(game->board, game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
