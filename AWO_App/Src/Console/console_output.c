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