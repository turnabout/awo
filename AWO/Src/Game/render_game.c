#include "Game/_game.h"

void render_game(Game* game)
{
    // Draw main sprites
    begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);


    end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
