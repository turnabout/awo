#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "AWO/Include/game.h"
#include "Command/command_list.h"

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

void nop_test()
{

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
    // Initialize list of commands that can be used through the commandline
    Command_List* list = create_commands_list((Command_Descriptor [MAX_CMD_COUNT]){
        {
            "init", 
            { Command_Arg_Int, Command_Arg_None },
            nop_test
        },
        {
            "run", 
            { Command_Arg_None },
            nop_test
        },
        {
            "exit", 
            { Command_Arg_None },
            nop_test
        },
        ""
    });

    if (list == NULL) {
        printf("Error creating list of commands\n");
        return;
    }

    /*
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
*/
    free_command_list(list);

    return 0;
}