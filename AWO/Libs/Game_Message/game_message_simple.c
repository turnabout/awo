#ifdef __EMSCRIPTEN__

#include <stdio.h>
#include <stdarg.h>

#include "Game_Message/game_message.h"

void push_msg(Game_Message_Label label, char* format, ...)
{
    va_list a_ptr;

    va_start(a_ptr, format);
    printf("%s\n", format, a_ptr);
    va_end(a_ptr);
}

#endif
