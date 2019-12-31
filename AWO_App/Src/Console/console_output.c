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

void print_console_message(Console* console, int color_pair, char* format, ...)
{
    // If the message count has reached the limit, remove older one and offset all others
    if (console->message_count >= MSG_COUNT_MAX) {
        return;
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
    for (int i = 0; i < console->message_count; i++) {
        print_message(console->messages[i], MSG_Y + i, MSG_X);
    }
}