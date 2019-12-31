#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    // Hide cursor
    curs_set(0);

    // Initialize colors
    start_color();
    init_pair(COLOR_PAIR_INFO, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_PAIR_ERROR, COLOR_RED, COLOR_BLACK);
}

void print_console_entered_command(Console* console)
{
    // Clear previous contents
    move(USER_CMD_Y, USER_CMD_X);
    clrtoeol();
    
    // Print the prompt
    mvprintw(USER_PROMPT_Y, USER_PROMPT_X, ">");
    refresh();

    // Print the user command
    mvprintw(USER_CMD_Y, USER_CMD_X, console->user_command);
    mvprintw(USER_CMD_Y, USER_CMD_X + console->user_command_char_count, "_");
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

    print_console_entered_command(console);

    return console;
}

static inline reset_console_user_command(Console* console)
{
    console->user_command[0] = '\0';
    console->user_command_char_count = 0;

    // Clear previous contents
    move(USER_CMD_Y, USER_CMD_X);
    clrtoeol();

    // Re-print the now-empty user command
    print_console_entered_command(console);
}

void print_console_message(Console* console, int color_pair, char* format, ...)
{
    char msg[1000];

    va_list a_ptr;

    va_start(a_ptr, format);
    vsprintf_s(msg, 1000, format, a_ptr);
    va_end(a_ptr);

    // Clear previous contents
    move(MSG_Y, MSG_X);
    clrtoeol();

    // Print new contents
    if (color_pair != COLOR_PAIR_NONE) {
        attron(COLOR_PAIR(color_pair));
    }

    mvprintw(MSG_Y, MSG_X, msg);

    if (color_pair != COLOR_PAIR_NONE) {
        attroff(COLOR_PAIR(color_pair));
    }
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

    // Initialize all possible chunks to NULL
    for (int i = 0; i <= CMD_ARG_MAX_COUNT; i++) {
        chunks[i] = NULL;
    }

    for (int i = 0; i <= COMMAND_MAX_LENGTH; i++) {
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
    
    // Error processing chunks
    if (chunks[0] == NULL) {
        print_console_message(console, COLOR_PAIR_ERROR, "Error processing command");
        return;
    }

    // Attempt to get the command
    Command* command = get_command_by_name(console->command_list, chunks[0]);

    // Error: Command not found
    if (command == NULL) {
        print_console_message(
            console, 
            COLOR_PAIR_ERROR, 
            "Error: command '%s' does not exist", 
            chunks[0]
        );

        reset_console_user_command(console);

        return;
    }

    // Confirm the command's arguments
    // TODO

    reset_console_user_command(console);
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
