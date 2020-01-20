#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "Message/message.h"

struct Message {

    // The message's string
    char* str;

    // The message's color pair
    int color_pair;
};

Message* create_message(char* message_str, int color_pair)
{
    Message* message = malloc(sizeof(Message));

    if (message == NULL) {
        return message;
    }

    message->color_pair = color_pair;

    // Allocate for message's string (+ 1 for null terminator)
    size_t message_len = strlen(message_str) + 1;
    message->str = malloc(message_len);

    if (message->str == NULL) {
        free(message);
        return NULL;
    }

    // Copy data into message's string
    strcpy_s(message->str, message_len, message_str);
    message->str[message_len - 1] = '\0';

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
        if (message->str != NULL) {
            free(message->str);
        }

        free(message);
    }
}