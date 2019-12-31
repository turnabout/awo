#include "Console/_console.h"

int cls(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    empty_console_messages(console);
    return CMD_Ret_OK;
}