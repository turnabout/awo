#pragma once

#include <AWO/Include/game.h>
#include <AWO/Include/game_message.h>

#include "Console/console.h"
#include "Console/Command/command_list.h"
#include "Console/Message/message.h"

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

// Max amount of messages the console can display at once
#define MSG_COUNT_MAX  10

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

    // List of every displayed messages
    Message* messages[MSG_COUNT_MAX];

    // Current count of displayed messages
    int message_count;

    // Reference to the game
    Game* game;

};

int update_console(Console* console);
int update_running_game_console(Console* console);
int process_console_command(Console* console);

void empty_console_messages(Console* console);

// Tile the console and game windows together
void tile_console(Console* console);

// Console output functions

// Process all game messages present in the game's messages stack
void process_console_game_messages(Console* console);
void add_console_message(Console* console, int color_pair, char* format, ...);
void print_console_entered_command(Console* console);
void print_console_messages(Console* console);
void reset_console_user_command(Console* console);

/*! @brief Creates the game and stores its initialized instance in the console.
 *
 *  @param[in] console The console module.
 *  @param[in] window_width (Command_Arg_Int) The game's initial window width.
 *  @param[in] window_height (Command_Arg_Int) The game's initial window height.
 */
int init(Console* console, void* payload[CMD_ARG_MAX_COUNT]);

/*! @brief Sets up and runs the game in design room mode.
 *
 *  @param[in] console The console module.
 */
int dr(Console* console, void* payload[CMD_ARG_MAX_COUNT]);

/*! @brief Stops and frees the currently running game instance.
 *
 *  @param[in] console The console module.
 */
int free_console_game(Console* console, void* payload[CMD_ARG_MAX_COUNT]);

/*! @brief Clears the console's list of messages.
 *
 *  @param[in] console The console module.
 */
int cls(Console* console, void* payload[CMD_ARG_MAX_COUNT]);
