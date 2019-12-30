#include <stdlib.h>

#include "Command/command.h"

Command* create_command()
{
    Command* command = malloc(sizeof(Command));

    return command;
}

void free_command(Command* command)
{
    if (command != NULL) {
        free(command);
    }
}