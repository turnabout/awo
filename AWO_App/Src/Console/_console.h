#pragma once

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
#define COLOR_PAIR_NONE  -1
#define COLOR_PAIR_INFO   1
#define COLOR_PAIR_ERROR  2

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

// List of command functions
void init(Console* console);
