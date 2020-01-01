#include "Include/game_message.h"

void start_message_service();
void push_msg(char* format, ...);
void push_msg_l(Game_Message_Label label, char* format, ...);
Game_Message* pop_msg();
void end_message_service();
