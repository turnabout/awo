#pragma once

#include <AWO/Include/game.h>

#include "Console/console.h"
#include "Console/Command/command_list.h"

// Max character length of a command
#define COMMAND_MAX_LENGTH 32

// Special keypad characters
#define NEW_LINE  10
#define SPACE     32
#define BACKSPACE  8
#define ESCAPE    27

// First and last valid symbol (letter/number/space/extra) characters
#define FIRST_SYMBOL_CHARACTER SPACE
#define LAST_SYMBOL_CHARACTER 'z'

// Curses color pairs
#define COLOR_PAIR_NONE    -1
#define COLOR_PAIR_INFO     1
#define COLOR_PAIR_ERROR    2
#define COLOR_PAIR_WARNING  3

// Positions in the console
#define USER_PROMPT_Y 0
#define USER_PROMPT_X 0

#define USER_CMD_Y 0
#define USER_CMD_X 2

#define MSG_Y 2
#define MSG_X 0

struct Console {

    // User's currently-entered command
    char user_command[COMMAND_MAX_LENGTH + 1];

    // Count of characters in the user's current command
    int user_command_char_count;

    // List of every command that can be used with the console
    Command_List* command_list;

    // Reference to the game
    Game* game;

};

int update_console(Console* console);
void process_console_command(Console* console);


// Console output functions
void print_console_entered_command(Console* console);
void print_console_message(Console* console, int color_pair, char* format, ...);
void reset_console_user_command(Console* console);

/*! @brief Creates the game and stores its initialized instance in the console.
 *
 *  @param[in] console The console module.
 *  @param[in] window_width (Command_Arg_Int) The game's initial window width.
 *  @param[in] window_height (Command_Arg_Int) The game's initial window height.
 */
void init(Console* console, void* payload[CMD_ARG_MAX_COUNT]);
