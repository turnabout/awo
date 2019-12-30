#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "Console/_console.h"

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

void print_console_prompt(Console* console)
{
    mvprintw(0, 0, ">");
    refresh();
}

void print_console_entered_command(Console* console)
{
    clear();
    print_console_prompt(console);
    mvprintw(0, 2, console->user_command);
    refresh();
}

Console* create_console()
{
    Console* console = malloc(sizeof(Console));

    if (console == NULL) {
        return NULL;
    }

    console->user_command_char_count = 0;
    console->user_command[0] = '\0';

    // Initialize list of commands that can be used through the console
    console->command_list = create_commands_list((Command_Descriptor [MAX_CMD_COUNT]){
        {
            "init", 
            { Command_Arg_Int, Command_Arg_None },
            NULL
        },
        {
            "run", 
            { Command_Arg_None },
            NULL
        },
        {
            "exit", 
            { Command_Arg_None },
            NULL
        },
        ""
    });

    if (console->command_list == NULL) {
        printf("Error creating command list\n");
        free_console(console);
        return NULL;
    }

    // Initialize Curses library for facilitating terminal usage
    initialize_curses();

    print_console_prompt(console);

    return console;
}

void update_console(Console* console, Game* game)
{
    int c = getch();

    // No character entered, exit right away
    if (c == ERR) {
        return;
    }

    // Process symbol character
    if (c >= FIRST_SYMBOL_CHARACTER && c <= LAST_SYMBOL_CHARACTER) {

        // Ignore if command max length has been reached
        if (console->user_command_char_count >= COMMAND_MAX_LENGTH) {
            return;
        }

        // Add character to current user command
        console->user_command[console->user_command_char_count++] = c;
        console->user_command[console->user_command_char_count] = '\0';

        // Print updated command
        print_console_entered_command(console);

        return;
    }

    // Process keypad characters
    switch (c) {
    case NEW_LINE:
        // Attempt to process the entered user command
        // process_console_command();
        break;

    case BACKSPACE:
        // Ignore if not a single character to delete
        if (console->user_command_char_count == 0) {
            return;
        }

        // Remove character from current user command
        console->user_command[--console->user_command_char_count] = '\0';

        // Print updated command
        print_console_entered_command(console);

        break;
    case KEY_UP:
        break;
    case KEY_DOWN:
        break;
    }
}

void free_console(Console* console)
{
    endwin();

    if (console == NULL) {
        return;
    }

    free(console);
}
