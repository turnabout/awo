#include <stdio.h>
#include <stdlib.h>

#include "AWO.h"

int main(int argc, char** argv)
{
    AWO* game;

    if ((game = create_game(0, 0)) == NULL) {
        printf("Failed to initialize game\n");
        free_game(game);
        return 1;
    }

    run_game(game);
    free_game(game);

    return 0;
}