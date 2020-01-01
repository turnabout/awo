#include <stdio.h>

#include "Include/game_message.h"
#include "Utilities/Message_Service/message_service.h"

Game_Message* get_next_game_message()
{
    return pop_msg();
}
