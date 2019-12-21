#include <stdio.h>

#include "Game/_game.h"
#include "Emscripten_Exports/emx.h"

// Updates the game's viewport dimensions.
void EMX update_game_size(Game* game, int width, int height)
{
    printf("New dimensions: {%d, %d}\n", width, height);
    update_game_window_dimensions(game, width, height);
}
