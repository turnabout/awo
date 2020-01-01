#include <stdio.h>
#include <curses.h>

#include "Console/_console.h"

void reset_console_user_command(Console* console)
{
    console->user_command[0] = '\0';
    console->user_command_char_count = 0;

    // Clear previous contents
    move(USER_CMD_Y, USER_CMD_X);
    clrtoeol();

    // Re-print the now-empty user command
    print_console_entered_command(console);
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

void print_console_messages(Console* console)
{
    for (int i = 0; i < console->message_count; i++) {
        print_message(console->messages[i], MSG_Y + i, MSG_X);
    }
}

void add_console_game_message(Console* console, Game_Message* message)
{
    int color_pair = COLOR_PAIR_NONE;

    switch (message->label) {
    case Error_Msg:
        color_pair = COLOR_PAIR_ERROR;
        break;
    case Warning_Msg:
        color_pair = COLOR_PAIR_WARNING;
        break;
    case Info_Msg:
        color_pair = COLOR_PAIR_INFO;
        break;
    }

    add_console_message(console, color_pair, message->str);
}

void add_console_message(Console* console, int color_pair, char* format, ...)
{
    // Check if the message count has reached the limit
    if (console->message_count >= MSG_COUNT_MAX) {

        // Remove oldest message
        free_message(console->messages[0]);

        // Offset other messages
        for (int i = 1; i < MSG_COUNT_MAX; i++) {
            console->messages[i - 1] = console->messages[i];
        }

        console->message_count--;
    }

    // Set the message's string
    char message_str[MSG_MAX_LENGTH];

    va_list a_ptr;

    va_start(a_ptr, format);
    vsprintf_s(message_str, MSG_MAX_LENGTH, format, a_ptr);
    va_end(a_ptr);

    // Add the new message
    console->messages[console->message_count++] = create_message(message_str, color_pair);

    // Print all messages
    print_console_messages(console);
}

void empty_console_messages(Console* console)
{
    for (int i = 0; i < console->message_count; i++) {
        // Clear value occupied by the message
        move(MSG_Y + i, MSG_X);
        clrtoeol();

        // Free the message
        free_message(console->messages[i]);
    }

    console->message_count = 0;
}