#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "AWO/Include/game.h"

static WINDOW* curses_win;

void game_run_callback(Game* game)
{
    // Read for character input, exit if none was found
    char c;
    if ((c = getch()) == ERR) {
        return;
    }

    refresh();
}

int main(int argc, char** argv)
{
    // Initialize PDCurses
    curses_win = initscr();

    // Make PDCurses' `getch` immediately return ERR if no input is waiting
    nodelay(curses_win, TRUE);

    // Initialize game & run
    Game* game;

    if ((game = create_game(0, 0)) == NULL) {
        printf("Failed to initialize game\n");
        free_game(game);
        return 1;
    }

    if (prepare_design_room_game(game)) {
        run_game(game, game_run_callback);
    }

    free_game(game);
    endwin();

    return 0;
}