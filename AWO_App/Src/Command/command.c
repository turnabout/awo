#include <stdlib.h>
#include <string.h>

#include "Command/command.h"

#pragma warning(disable: 6011 )
#pragma warning(disable: 6387 )

Command* create_command(
    const char* name,
    Command_Arg_Type arg_types[COMMAND_ARG_MAX_COUNT],
    void* function
)
{
    Command* command = malloc(sizeof(Command));

    command->function = function;

    // Set name
    command->name = malloc((sizeof(char) * strlen(name)) + 1);
    strcpy_s(command->name, strlen(name) + 1, name);

    // Gather command argument data
    for (int i = 0; i < COMMAND_ARG_MAX_COUNT; i++) {
        if (arg_types[i] == Command_Arg_None || i == COMMAND_ARG_MAX_COUNT) {
            command->arg_count = i;
            break;
        }

        command->arg_types[i] = arg_types[i];
    }

    return command;
}

void free_command(Command* command)
{
    if (command == NULL) {
        return;
    }

    if (command->name != NULL) {
        free(command->name);
    }

    free(command);
}