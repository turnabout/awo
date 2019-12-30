#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "AWO/Include/game.h"
#include "Command/command_list.h"

#define COLOR_PAIR_AUTO_COMPLETE 1
#define COMMAND_MAX_LENGTH 32

#define SPACE     32
#define BACKSPACE  8

// First and last valid symbol (letter/number/space/extra) characters
#define FIRST_SYMBOL_CHARACTER SPACE
#define LAST_SYMBOL_CHARACTER 'z'

static char user_command[COMMAND_MAX_LENGTH + 1] = "";
static int user_command_char_count = 0;

void print_prompt()
{
    mvprintw(0, 0, ">");
    refresh();
}

void print_entered_command()
{
    print_prompt();
    mvprintw(0, 2, user_command);
    refresh();
}

void game_run_callback(Game* game)
{
    int c = getch();

    // No character entered, exit right away
    if (c == ERR) {
        return;
    }

    // Process symbol character
    if (c >= FIRST_SYMBOL_CHARACTER && c <= LAST_SYMBOL_CHARACTER) {

        // Ignore if command max length has been reached
        if (user_command_char_count >= COMMAND_MAX_LENGTH) {
            return;
        }

        // Add character to current user command
        user_command[user_command_char_count++] = c;
        user_command[user_command_char_count] = '\0';

        // Print updated command
        print_entered_command();

        return;
    }

    // Process keypad characters
    switch (c) {
    case BACKSPACE:
        break;
    case KEY_UP:
        break;
    case KEY_DOWN:
        break;
    }
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

    // Initialize Curses for terminal functionality
    initialize_curses();
    print_prompt();

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
    free_command_list(list);

    return 0;
}