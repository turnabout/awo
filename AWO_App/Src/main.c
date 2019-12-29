#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "AWO/Include/game.h"

#define COLOR_PAIR_AUTO_COMPLETE 1

void game_run_callback(Game* game)
{
    // Read for character input, exit if none was found
    char c;
    if ((c = getch()) == ERR) {
        return;
    }


    attron(A_BOLD);
    attron(COLOR_PAIR(COLOR_PAIR_AUTO_COMPLETE));
    printw("Entered: ");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(COLOR_PAIR_AUTO_COMPLETE));
    printw("%c\n", c);

    refresh();
}

void initialize_curses()
{
    initscr();

    // Process additional inputs (arrow keys, F keys, etc)
    keypad(stdscr, TRUE);

    // Don't automatically echo back user input
    noecho();

    // Make Curses' `getch` immediately return ERR if no input is waiting
    nodelay(stdscr, TRUE);

    // Initialize colors
    start_color();
    init_pair(COLOR_PAIR_AUTO_COMPLETE, COLOR_BLACK, COLOR_WHITE);
}

int main(int argc, char** argv)
{
    // Initialize Curses for terminal functionality
    initialize_curses();

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