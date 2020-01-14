#ifndef __EMSCRIPTEN__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "Linked_List/linked_list.h"
#include "Message_Service/message_service.h"

static Linked_List* list = NULL;

void start_message_service()
{
    if (list != NULL) {
        return;
    }

    list = create_linked_list(NULL, 0);
}

void push_msg(Game_Message_Label label, char* format, ...)
{
    if (list == NULL) {
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

    // Write to the message string buffer
    vsprintf_s(message->str, msg_len, format, a_ptr);
    message->str[msg_len - 1] = '\0';

    va_end(a_ptr);

    // Store message in message service's list
    append_linked_list_item(list, (void*)message);
}

Game_Message* pop_msg()
{
    if (list == NULL) {
        return NULL;
    }

    Game_Message* message = get_linked_list_nth_element(list, 0);

    if (message != NULL) {
        delete_linked_list_item(list, (void*)message, FALSE);
    }

    return message;
}

void end_message_service()
{
    if (list == NULL) {
        return;
    }

    free_linked_list(list);
    list = NULL;
}

#endif