#include <stdio.h>
#include <stdlib.h>

#include "Include/game_message.h"

void free_game_message(Game_Message* message)
{
    if (message != NULL) {

        if (message->str != NULL) {
            free(message->str);
        }

        free(message);
    }
}