#include <stdio.h>
#include <stdlib.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define RESOURCES_PATH_BASE TOSTRING(SOLUTION_DIR) "AWO\\Resources\\"

#include "conf.h"
#include "Game/game.h"

int main(int argc, char** argv)
{
    Game* game;

    printf("Base path for resources: %s\n", RESOURCES_PATH_BASE);

    return;

    if ((game = init_game(
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT
    )) == NULL) {
        printf("Failed to initialize game\n");
        exit_game(game);
        return 1;
    }

    run_game(game);
    exit_game(game);

    return 0;
}