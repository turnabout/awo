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

    // Don't use nodelay mode initially
    nodelay(stdscr, FALSE);

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
            init
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

void process_console_command(Console* console)
{
    // Exit early if user command is empty
    if (console->user_command_char_count == 0) {
        return;
    }

    // Translate the user-entered command string into usable chunks
    char* chunks[1 + CMD_ARG_MAX_COUNT];
    int chunk_count = 0;
    int next_chunk_start = 0;

    for (int i = 0; i < COMMAND_MAX_LENGTH; i++) {
        if (console->user_command[i] == '\0') {

            if (i > 0) {
                chunks[chunk_count++] = &(console->user_command[next_chunk_start]);
            }

            break;
        }

        if (console->user_command[i] == ' ') {
            chunks[chunk_count++] = &(console->user_command[next_chunk_start]);
            next_chunk_start = i + 1;
            console->user_command[i] = '\0';
        }
    }

    // Reset the user command
    console->user_command[0] = '\0';
    console->user_command_char_count = 0;
    
    // Test
    mvprintw(1, 0, "Chunk count: %d", chunk_count);

    for (int i = 0; i < chunk_count; i++) {
        mvprintw(2 + i, 0, "%s", chunks[i]);
    }

    // Use the chunks to try and fetch an actual command corresponding to it
    // Command* command;
}

int update_console(Console* console)
{
    int c = getch();

    // No character entered (for nodelay mode), exit right away
    if (c == ERR) {
        return 0;
    }

    // Escape, return negative result (for delay mode)
    if (c == ESCAPE) {
        return 0;
    }

    // Process symbol character
    if (c >= FIRST_SYMBOL_CHARACTER && c <= LAST_SYMBOL_CHARACTER) {

        // Ignore if command max length has been reached
        if (console->user_command_char_count >= COMMAND_MAX_LENGTH) {
            return 1;
        }

        // Add character to current user command
        console->user_command[console->user_command_char_count++] = c;
        console->user_command[console->user_command_char_count] = '\0';

        // Print updated command
        print_console_entered_command(console);

        return 1;
    }

    // Process keypad characters
    switch (c) {
    case NEW_LINE:
        // Attempt to process the entered user command
        process_console_command(console);
        break;

    case BACKSPACE:
        // Ignore if not a single character to delete
        if (console->user_command_char_count == 0) {
            return 1;
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

    return 1;
}

void run_console(Console* console)
{
    while (update_console(console)) {
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
