#include "Console/_console.h"

void cls(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    empty_console_messages(console);
}