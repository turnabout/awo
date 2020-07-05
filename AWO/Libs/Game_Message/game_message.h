#pragma once
#include "AWO/game_message.h"

// Macro shortcuts for pushing messages with different labels
#define printe(format, ...) push_msg(Error_Msg, format, ##__VA_ARGS__)
#define printi(format, ...) push_msg(Info_Msg, format, ##__VA_ARGS__)
#define printw(format, ...) push_msg(Warning_Msg, format, ##__VA_ARGS__)
#define printm(format, ...) push_msg(Plain_Msg, format, ##__VA_ARGS__)

/*! @brief Pushes a game message, to be handled by an external source.
 *
 *  @param[in] label The label the pushed game message should have.
 *  @param[in] format The formatted message + arguments. Use the same way as `printf`.
 */
void push_msg(Game_Message_Label label, char* format, ...);
