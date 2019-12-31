#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "Console/Message/message.h"

struct Message {

    // The message's string
    char str[MSG_MAX_LENGTH];

    // The message's color pair
    int color_pair;
};

Message* create_message(char message_str[MSG_MAX_LENGTH], int color_pair)
{
    Message* message = malloc(sizeof(Message));

    if (message == NULL) {
        return message;
    }

    message->color_pair = color_pair;
    strcpy_s(message->str, MSG_MAX_LENGTH, message_str);

    return message;
}

void print_message(Message* message, int y, int x)
{
    if (message == NULL) {
        return;
    }

    // Clear previous value
    move(y, x);
    clrtoeol();

    // Print the message's value
    if (message->color_pair != COLOR_PAIR_NONE) {
        attron(COLOR_PAIR(message->color_pair));
    }

    mvprintw(y, x, message->str);

    if (message->color_pair != COLOR_PAIR_NONE) {
        attroff(COLOR_PAIR(message->color_pair));
    }
}

void free_message(Message* message)
{
    if (message != NULL) {
        free(message);
    }
}