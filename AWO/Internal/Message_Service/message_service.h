#include "Include/game_message.h"

// Macro shortcuts for pushing messages with different labels
#define printe(format, ...) push_msg(Error_Msg, format, ##__VA_ARGS__)
#define printi(format, ...) push_msg(Info_Msg, format, ##__VA_ARGS__)
#define printw(format, ...) push_msg(Warning_Msg, format, ##__VA_ARGS__)
#define printm(format, ...) push_msg(Plain_Msg, format, ##__VA_ARGS__)

void start_message_service();
void push_msg(Game_Message_Label label, char* format, ...);
Game_Message* pop_msg();
void end_message_service();
