#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    init_pair(COLOR_PAIR_WARNING, COLOR_YELLOW, COLOR_BLACK);
}

void console_game_message_cb(Game_Message* message, Console* console)
{
    int message_color_pair;

    switch (message->label) {
    case Error_Msg:
        message_color_pair = COLOR_PAIR_ERROR;
        break;
    case Warning_Msg:
        message_color_pair = COLOR_PAIR_WARNING;
        break;
    case Info_Msg:
        message_color_pair = COLOR_PAIR_INFO;
        break;
    default:
        message_color_pair = COLOR_PAIR_NONE;
        break;
    }

    add_console_message(console, message_color_pair, message->str);
}

Console* create_console()
{
    Console* console = malloc(sizeof(Console));

    if (console == NULL) {
        return NULL;
    }

    console->user_command_char_count = 0;
    console->user_command[0] = '\0';
    console->game = NULL;
    console->message_count = 0;

    // Initialize list of commands that can be used through the console
    console->command_list = create_commands_list((Command_Descriptor [MAX_CMD_COUNT]){
        {
            "dr", 
            { Command_Arg_None },
            dr
        },
        {
            "tile",
            { Command_Arg_Int },
            update_editor_tile
        },
        {
            "cls", 
            { Command_Arg_None },
            cls
        },
        {
            "size", 
            { Command_Arg_Int, Command_Arg_Int },
            size
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

    // Set callback for handling messages emitted by the game
    set_game_message_callback(console_game_message_cb, (void*)console);

    // Initialize the essential game window/data modules
    console->game_data = create_game_data();
    console->game_window = create_game_window(0, 0);

    if (console->game_data == NULL || console->game_window == NULL) {
        free_console(console);
        return NULL;
    }

    return console;
}

int update_console(Console* console)
{
    int c = getch();

    // No character entered (for nodelay mode), exit right away
    if (c == ERR) {
        return CMD_Ret_Error;
    }

    // Escape, return negative result (for delay mode)
    if (c == ESCAPE) {
        return CMD_Ret_Exit;
    }

    // Process symbol character
    if (c >= FIRST_SYMBOL_CHARACTER && c <= LAST_SYMBOL_CHARACTER) {

        // Ignore if command max length has been reached
        if (console->user_command_char_count >= COMMAND_MAX_LENGTH) {
            return CMD_Ret_OK;
        }

        // Add character to current user command
        console->user_command[console->user_command_char_count++] = c;
        console->user_command[console->user_command_char_count] = '\0';

        // Print updated command
        print_console_entered_command(console);

        return CMD_Ret_OK;
    }

    // Process keypad characters
    int res;

    switch (c) {
    case NEW_LINE:
        // Attempt to process the entered user command
        res = process_console_command(console);
        reset_console_user_command(console);
        return res;

    case BACKSPACE:
        // Ignore if not a single character to delete
        if (console->user_command_char_count == 0) {
            return CMD_Ret_OK;
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

    return CMD_Ret_OK;
}

void run_console(Console* console)
{
    while (update_console(console) != CMD_Ret_Exit);
}

void send_console_command(Console* console, char* user_command)
{
    int i;
    for (i = 0; (user_command[i] != '\0' || i >= CMD_NAME_MAX_LENGTH); i++) {
        console->user_command[i] = user_command[i];
    }

    console->user_command[i] = '\0';
    console->user_command_char_count = i;

    process_console_command(console);
}

void free_console(Console* console)
{
    if (stdscr != NULL) {
        endwin();
    }

    if (console == NULL) {
        return;
    }

    empty_console_messages(console);

    free_game_data(console->game_data);
    free_game_window(console->game_window);
    free(console);
}
