#include <stdlib.h>
#include <string.h>

#include "Command/command.h"

#pragma warning(disable: 6011 )
#pragma warning(disable: 6387 )

struct Command {

    // The name of this command.
    char name[CMD_NAME_MAX_LENGTH];

    // The count of commands.
    int arg_count;

    // The type of the command's arguments.
    Command_Arg_Type arg_types[CMD_ARG_MAX_COUNT];

    // Function that should be called by this command.
    void* function;

};

Command* create_command(Command_Descriptor descriptor)
{
    Command* command = malloc(sizeof(Command));

    command->function = descriptor.function;

    // Set name
    strcpy_s(command->name, strlen(descriptor.name) + 1, descriptor.name);

    // Gather command argument data
    for (int i = 0; i < CMD_ARG_MAX_COUNT; i++) {
        if (descriptor.arg_types[i] == Command_Arg_None || i == CMD_ARG_MAX_COUNT) {
            command->arg_count = i;
            break;
        }

        command->arg_types[i] = descriptor.arg_types[i];
    }

    return command;
}

char* get_command_name(Command* command)
{
    return command->name;
}

void free_command(Command* command)
{
    if (command == NULL) {
        return;
    }

    free(command);
}