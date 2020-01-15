#include "Include/Game_Message/game_message.h"

// Macro shortcuts for pushing messages with different labels
#define printe(format, ...) push_msg(Error_Msg, format, ##__VA_ARGS__)
#define printi(format, ...) push_msg(Info_Msg, format, ##__VA_ARGS__)
#define printw(format, ...) push_msg(Warning_Msg, format, ##__VA_ARGS__)
#define printm(format, ...) push_msg(Plain_Msg, format, ##__VA_ARGS__)
