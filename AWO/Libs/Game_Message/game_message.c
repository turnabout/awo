#ifndef __EMSCRIPTEN__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "Game_Message/game_message.h"

// Function handling game messages
static Game_Message_CB message_callback = NULL;

void set_game_message_callback(Game_Message_CB callback)
{
    message_callback = callback;
}

void push_msg(Game_Message_Label label, char* format, ...)
{
    if (message_callback == NULL) {
        return;
    }

    Game_Message* message = malloc(sizeof(Game_Message));

    if (message == NULL) {
        return;
    }

    message->label = label;

    // Copy string into message
    va_list a_ptr;

    va_start(a_ptr, format);

    // Get length to allocate for message buffer (+ 1 for null terminator)
    size_t msg_len = vsnprintf(NULL, 0, format, a_ptr) + 1;
    message->str = malloc(msg_len);

    if (message->str == NULL) {
        free(message->str);
        free(message);
        return;
    }

    // Write to the message string buffer
    vsprintf_s(message->str, msg_len, format, a_ptr);
    message->str[msg_len - 1] = '\0';

    va_end(a_ptr);

    // Send the message to the set message callback
    message_callback(message);
    free(message);
}

#endif